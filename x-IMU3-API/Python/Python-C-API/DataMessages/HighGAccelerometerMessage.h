// This file was generated by x-IMU3-API/Rust/src/data_messages/generate_data_messages.py

#ifndef HIGH_G_ACCELEROMETER_MESSAGE_H
#define HIGH_G_ACCELEROMETER_MESSAGE_H

#include "../../../C/Ximu3.h"
#include <Python.h>

typedef struct
{
    PyObject_HEAD
    XIMU3_HighGAccelerometerMessage message;
} HighGAccelerometerMessage;

static void high_g_accelerometer_message_free(HighGAccelerometerMessage* self)
{
    Py_TYPE(self)->tp_free(self);
}

static PyObject* high_g_accelerometer_message_get_timestamp(HighGAccelerometerMessage* self)
{
    return Py_BuildValue("K", self->message.timestamp);
}

static PyObject* high_g_accelerometer_message_get_x(HighGAccelerometerMessage* self)
{
    return Py_BuildValue("f", self->message.x);
}

static PyObject* high_g_accelerometer_message_get_y(HighGAccelerometerMessage* self)
{
    return Py_BuildValue("f", self->message.y);
}

static PyObject* high_g_accelerometer_message_get_z(HighGAccelerometerMessage* self)
{
    return Py_BuildValue("f", self->message.z);
}

static PyObject* high_g_accelerometer_message_to_string(HighGAccelerometerMessage* self, PyObject* args)
{
    return Py_BuildValue("s", XIMU3_high_g_accelerometer_message_to_string(self->message));
}

static PyGetSetDef high_g_accelerometer_message_get_set[] = {
        { "timestamp", (getter) high_g_accelerometer_message_get_timestamp, NULL, "", NULL },
        { "x",         (getter) high_g_accelerometer_message_get_x,         NULL, "", NULL },
        { "y",         (getter) high_g_accelerometer_message_get_y,         NULL, "", NULL },
        { "z",         (getter) high_g_accelerometer_message_get_z,         NULL, "", NULL },
        { NULL }  /* sentinel */
};

static PyMethodDef high_g_accelerometer_message_methods[] = {
        { "to_string", (PyCFunction) high_g_accelerometer_message_to_string, METH_NOARGS, "" },
        { NULL } /* sentinel */
};

static PyTypeObject high_g_accelerometer_message_object = {
        PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "ximu3.HighGAccelerometerMessage",
        .tp_basicsize = sizeof(HighGAccelerometerMessage),
        .tp_dealloc = (destructor) high_g_accelerometer_message_free,
        .tp_getset = high_g_accelerometer_message_get_set,
        .tp_methods = high_g_accelerometer_message_methods,
};

static PyObject* high_g_accelerometer_message_from(const XIMU3_HighGAccelerometerMessage* const message)
{
    HighGAccelerometerMessage* const self = (HighGAccelerometerMessage*) high_g_accelerometer_message_object.tp_alloc(&high_g_accelerometer_message_object, 0);
    self->message = *message;
    return (PyObject*) self;
}

static void high_g_accelerometer_message_callback(XIMU3_HighGAccelerometerMessage data, void* context)
{
    const PyGILState_STATE state = PyGILState_Ensure();

    PyObject* const object = high_g_accelerometer_message_from(&data);
    PyObject* const tuple = Py_BuildValue("(O)", object);
    Py_DECREF(PyObject_CallObject((PyObject*) context, tuple));
    Py_DECREF(tuple);
    Py_DECREF(object);

    PyGILState_Release(state);
}

#endif
