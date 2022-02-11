// This file was generated by x-IMU3-API/Rust/src/data_messages/generate_data_messages.py

#ifndef MAGNETOMETER_MESSAGE_H
#define MAGNETOMETER_MESSAGE_H

#include "../../../C/Ximu3.h"
#include <Python.h>

typedef struct
{
    PyObject_HEAD
    XIMU3_MagnetometerMessage message;
} MagnetometerMessage;

static void magnetometer_message_free(MagnetometerMessage* self)
{
    Py_TYPE(self)->tp_free(self);
}

static PyObject* magnetometer_message_get_timestamp(MagnetometerMessage* self)
{
    return Py_BuildValue("K", self->message.timestamp);
}

static PyObject* magnetometer_message_get_x_axis(MagnetometerMessage* self)
{
    return Py_BuildValue("f", self->message.x_axis);
}

static PyObject* magnetometer_message_get_y_axis(MagnetometerMessage* self)
{
    return Py_BuildValue("f", self->message.y_axis);
}

static PyObject* magnetometer_message_get_z_axis(MagnetometerMessage* self)
{
    return Py_BuildValue("f", self->message.z_axis);
}

static PyObject* magnetometer_message_to_string(MagnetometerMessage* self, PyObject* args)
{
    return Py_BuildValue("s", XIMU3_magnetometer_message_to_string(self->message));
}

static PyGetSetDef magnetometer_message_get_set[] = {
        { "timestamp", (getter) magnetometer_message_get_timestamp, NULL, "", NULL },
        { "x_axis",    (getter) magnetometer_message_get_x_axis,    NULL, "", NULL },
        { "y_axis",    (getter) magnetometer_message_get_y_axis,    NULL, "", NULL },
        { "z_axis",    (getter) magnetometer_message_get_z_axis,    NULL, "", NULL },
        { NULL }  /* sentinel */
};

static PyMethodDef magnetometer_message_methods[] = {
        { "to_string", (PyCFunction) magnetometer_message_to_string, METH_NOARGS, "" },
        { NULL } /* sentinel */
};

static PyTypeObject magnetometer_message_object = {
        PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "ximu3.MagnetometerMessage",
        .tp_basicsize = sizeof(MagnetometerMessage),
        .tp_dealloc = (destructor) magnetometer_message_free,
        .tp_getset = magnetometer_message_get_set,
        .tp_methods = magnetometer_message_methods,
};

static PyObject* magnetometer_message_from(const XIMU3_MagnetometerMessage* const message)
{
    MagnetometerMessage* const self = (MagnetometerMessage*) magnetometer_message_object.tp_alloc(&magnetometer_message_object, 0);
    self->message = *message;
    return (PyObject*) self;
}

typedef struct
{
    PyObject* callable;
    XIMU3_MagnetometerMessage data;
} MagnetometerPendingCallArg;

static int magnetometer_message_pending_call_func(void* arg)
{
    PyObject* const object = magnetometer_message_from(&((MagnetometerPendingCallArg*) arg)->data);
    PyObject* const tuple = Py_BuildValue("(O)", object);
    Py_DECREF(PyObject_CallObject(((MagnetometerPendingCallArg*) arg)->callable, tuple));
    Py_DECREF(tuple);
    Py_DECREF(object);
    free(arg);
    return 0;
}

static void magnetometer_message_callback(XIMU3_MagnetometerMessage data, void* context)
{
    MagnetometerPendingCallArg* const arg = malloc(sizeof(MagnetometerPendingCallArg));
    arg->callable = (PyObject*) context;
    arg->data = data;
    Py_AddPendingCall(&magnetometer_message_pending_call_func, arg);
}

#endif
