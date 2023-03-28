#include "../CustomLookAndFeel.h"
#include "Convert.h"
#include "ThreeDView.h"

ThreeDView::Settings& ThreeDView::Settings::operator=(const ThreeDView::Settings& other)
{
    azimuth = other.azimuth.load();
    elevation = other.elevation.load();
    zoom = other.zoom.load();
    isModelEnabled = other.isModelEnabled.load();
    isStageEnabled = other.isStageEnabled.load();
    isAxesEnabled = other.isAxesEnabled.load();
    model = other.model.load();
    axesConvention = other.axesConvention.load();
    return *this;
}

ThreeDView::ThreeDView(GLRenderer& renderer_) : OpenGLComponent(renderer_.getContext()),
                                                renderer(renderer_)
{
    renderer.addComponent(*this);
}

ThreeDView::~ThreeDView()
{
    renderer.removeComponent(*this);
}

void ThreeDView::render()
{
    const auto bounds = toOpenGLBounds(getBoundsInMainWindow());
    auto& resources = renderer.getResources();

    resources.threeDViewShader.use();
    renderer.refreshScreen(juce::Colours::black, bounds);
    resources.threeDViewShader.projectionMatrix.setMatrix4(renderer.getProjectionMatrix(bounds).mat, 1, false);

    const auto worldRotation = rotation(settings.elevation, settings.azimuth, 0.0f) * rotation(90.0f, 0.0f, 0.0f);
    const auto worldTransformation = translation(0.0f, 0.0f, settings.zoom) * worldRotation;
    const auto deviceRotation = juce::Quaternion<GLfloat>(-1.0f * quaternionX, -1.0f * quaternionY, -1.0f * quaternionZ, quaternionW).getRotationMatrix(); // quaternion conjugate
    auto axesConventionRotation = rotation(0.0f, 0.0f, 0.0f);

    switch (settings.axesConvention.load())
    {
        case AxesConvention::nwu:
            break;
        case AxesConvention::enu:
            axesConventionRotation = rotation(0.0f, 0.0f, 90.0f);
            break;
        case AxesConvention::ned:
            axesConventionRotation = rotation(180.0f, 0.0f, 0.0f);
            break;
    }

    const auto lightAmbient = juce::Vector3D<GLfloat>(1.0f, 1.0f, 1.0f);
    const auto lightDiffuse = juce::Vector3D<GLfloat>(1.0f, 1.0f, 1.0f);
    const auto lightSpecular = juce::Vector3D<GLfloat>(1.0f, 1.0f, 1.0f);
    const auto lightPosition = juce::Vector3D<GLfloat>(3.0f, 3.0f, 0.0f);

    resources.threeDViewShader.lightIntensity.set(0.5f);
    resources.threeDViewShader.lightColour.set(1.0f, 1.0f, 1.0f, 1.0f);
    resources.threeDViewShader.lightPosition.set(lightPosition.x, lightPosition.y, lightPosition.z);

    // TODO: comment what each of these does
    resources.threeDViewShader.emissivity.set(0.5f);
    resources.threeDViewShader.maxSpecularRange.set(10.0f); // low = glossy. high = matte
    resources.threeDViewShader.specularFactor.set(1.0f); // low = glossy. high = matte

    resources.threeDViewShader.cameraPosition.set(0.0f, 0.0f, 0.0f);

    //Please note - These values are for the alternative lighting shader that uses materials
    //They can be passed each frame call, but will only become effective when the 'threeDViewShaderWithMaterial' is in use
    resources.threeDViewShaderWithMaterial.lightAmbient.set(lightAmbient.x, lightAmbient.y, lightAmbient.z);
    resources.threeDViewShaderWithMaterial.lightDiffuse.set(lightDiffuse.x, lightDiffuse.y, lightDiffuse.z);
    resources.threeDViewShaderWithMaterial.lightSpecular.set(lightSpecular.x, lightSpecular.y, lightSpecular.z);
    resources.threeDViewShaderWithMaterial.lightPosition.set(lightPosition.x, lightPosition.y, lightPosition.z);

    const auto calcMatrix = [&](juce::Matrix3D<float> matrixArg, juce::Vector3D<float> vector)
    {
        auto matrix = matrixArg * juce::Matrix3D<float>::fromTranslation(vector);
        auto newMatrix = juce::Matrix3D<float> {};
        newMatrix.mat[12] = matrix.mat[12];
        newMatrix.mat[13] = matrix.mat[13];
        newMatrix.mat[14] = matrix.mat[14];
        return newMatrix;
    };

    if (settings.isModelEnabled)
    {
        resources.threeDViewShader.emissivity.set(0.8f);
        resources.threeDViewShader.modelMatrix.setMatrix4((worldTransformation * axesConventionRotation * deviceRotation).mat, 1, false);

        switch (settings.model.load())
        {
            case Model::board:
                resources.board.render(resources, false);
                break;
            case Model::housing:
                resources.housing.render(resources, false);
                break;
            case Model::custom:
                resources.custom.render(resources, false);
                break;
        }
    }

    // TODO:   if ((resources.board.getIsLoaded() == false) || (resources.housing.getIsLoaded() == false) || (resources.custom.getIsLoaded() == false)) { }

    if (settings.isStageEnabled)
    {
        resources.threeDViewShader.emissivity.set(0.0f);
        resources.threeDViewShader.isTextured.set(true);
        resources.compassTexture.bind();
        resources.threeDViewShader.modelMatrix.setMatrix4((worldTransformation * translation(0.0f, 0.0f, -0.5f) * scale(1.5f)).mat, 1, false);
        resources.stage.setColor(1.0f, 1.0f, 1.0f, 0.75f);
        resources.stage.render(resources, true);
        resources.compassTexture.unbind();
        resources.threeDViewShader.isTextured.set(false);
    }

    if (settings.isAxesEnabled)
    {
        resources.threeDViewShader.emissivity.set(0.3f);

        renderer.turnDepthTestOff(); // axes brought to front

        auto renderAxes = [&](const auto& matrix)
        {
            const auto alpha = 0.5f;

            resources.threeDViewShader.modelMatrix.setMatrix4(matrix.mat, 1, false);
            resources.arrow.setColor(1.0f, 0.0f, 0.0f, alpha);
            resources.arrow.render(resources, false);

            resources.threeDViewShader.modelMatrix.setMatrix4((matrix * juce::Quaternion<GLfloat>(0.7071f, 0.7071f, 0.0f, 0.0f).getRotationMatrix()).mat, 1, false);
            resources.arrow.setColor(0.0f, 1.0f, 0.0f, alpha);
            resources.arrow.render(resources, false);

            resources.threeDViewShader.modelMatrix.setMatrix4((matrix * juce::Quaternion<GLfloat>(0.0f, 0.7071f, 0.0f, 0.7071f).getRotationMatrix()).mat, 1, false);
            resources.arrow.setColor(0.0f, 0.0f, 1.0f, alpha);
            resources.arrow.render(resources, false);
        };

        const auto bottomLeftX = -0.45f;
        const auto bottomLeftY = -0.2f;

        renderAxes(translation(0.0f, 0.0f, -1.0f) * worldRotation * axesConventionRotation * deviceRotation * scale(0.1f));
        renderAxes(translation(bottomLeftX, bottomLeftY, -1.0f) * worldRotation * axesConventionRotation * scale(0.1f));

        renderer.turnCullingOff(); // render text only after culling off
        renderer.getResources().textShader.use();

        const auto renderText = [&](Text& text, const juce::String& label, const juce::Colour& colour, juce::Matrix3D<float> matrix)
        {
            text.setText(label);
            text.setColour(colour);

            const juce::Point<GLfloat> pixelSize(2.0f / bounds.getWidth(), 2.0f / bounds.getHeight());
            text.setScale({ pixelSize.x, pixelSize.y });

            juce::Vector3D<GLfloat> position(matrix.mat[12], matrix.mat[13], matrix.mat[14]);
            auto clipCoordinate = renderer.getProjectionMatrix(bounds) * juce::Matrix3D<GLfloat>::fromTranslation(position);

            auto x = clipCoordinate.mat[12] / clipCoordinate.mat[15];
            auto y = clipCoordinate.mat[13] / clipCoordinate.mat[15];

            auto ndcMatrix = juce::Matrix3D<float> {};
            ndcMatrix.mat[12] = x;
            ndcMatrix.mat[13] = y;

            resources.textShader.transformation.setMatrix4(ndcMatrix.mat, 1, false);
            text.render(resources);
        };

        auto matrixA = translation(0.0f, 0.0f, -1.0f) * worldRotation * axesConventionRotation * deviceRotation * scale(0.11f);
        renderText(resources.get3DViewAxisText(), "X", juce::Colours::darkred, calcMatrix(matrixA, juce::Vector3D<float>(1.0f, 0.0f, 0.0f)));
        renderText(resources.get3DViewAxisText(), "Y", juce::Colours::green, calcMatrix(matrixA, juce::Vector3D<float>(0.0f, 1.0f, 0.0f)));
        renderText(resources.get3DViewAxisText(), "Z", juce::Colours::blue, calcMatrix(matrixA, juce::Vector3D<float>(0.0f, 0.0f, 1.0f)));

        auto matrixB = translation(bottomLeftX, bottomLeftY, -1.0f) * worldRotation * axesConventionRotation * scale(0.11f);
        renderText(resources.get3DViewAxisText(), "X", juce::Colours::darkred, calcMatrix(matrixB, juce::Vector3D<float>(1.0f, 0.0f, 0.0f)));
        renderText(resources.get3DViewAxisText(), "Y", juce::Colours::green, calcMatrix(matrixB, juce::Vector3D<float>(0.0f, 1.0f, 0.0f)));
        renderText(resources.get3DViewAxisText(), "Z", juce::Colours::blue, calcMatrix(matrixB, juce::Vector3D<float>(0.0f, 0.0f, 1.0f)));
    }
}

void ThreeDView::update(const float x, const float y, const float z, const float w)
{
    quaternionX = x;
    quaternionY = y;
    quaternionZ = z;
    quaternionW = w;
}

void ThreeDView::setSettings(const Settings& settings_)
{
    settings = settings_;
}

void ThreeDView::setCustomModel(const juce::File& file)
{
    renderer.getResources().custom.setModel(file);
}

bool ThreeDView::isLoading() const
{
    switch (settings.model.load())
    {
        case Model::board:
            return renderer.getResources().board.isLoading();

        case Model::housing:
            return renderer.getResources().housing.isLoading();

        case Model::custom:
            return renderer.getResources().custom.isLoading();
    }

    return false;
}

juce::Matrix3D<GLfloat> ThreeDView::rotation(const float roll, const float pitch, const float yaw)
{
    return Convert::toQuaternion(roll, pitch, yaw).getRotationMatrix();
}

juce::Matrix3D<GLfloat> ThreeDView::translation(const float x, const float y, const float z)
{
    return juce::Matrix3D<GLfloat>::fromTranslation(juce::Vector3D<GLfloat>(x, y, z));
}

juce::Matrix3D<GLfloat> ThreeDView::scale(const float value)
{
    juce::Matrix3D<GLfloat> matrix;
    matrix.mat[0] = value;
    matrix.mat[5] = value;
    matrix.mat[10] = value;
    return matrix;
}
