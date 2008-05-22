/* $Id$ */

/* ---------------------------------------------------------------- */

#include "Python.h"

#include "mpi.h"

/* XXX describe */
#if defined(PyMPI_HAVE_CONFIG_H)
#include "config.h"
#else
#if defined(MPICH_NAME) && MPICH_NAME==2
#include "config/mpich2.h"
#elif defined(OPEN_MPI)
#include "config/openmpi.h"
#elif defined(DEINO_MPI)
#include "config/deinompi.h"
#elif defined(MPICH_NAME) && MPICH_NAME==1
#include "config/mpich1.h"
#elif defined(LAM_MPI)
#include "config/lammpi.h"
#endif
#endif

/* XXX describe */
#include "missing.h"
#include "compat/anympi.h"

/* XXX describe */
#if   defined(MPICH_NAME) && MPICH_NAME==2
#include "compat/mpich2.h"
#elif defined(OPEN_MPI)
#include "compat/openmpi.h"
#elif defined(DEINO_MPI)
#include "compat/deinompi.h"
#elif defined(MPICH_NAME) && MPICH_NAME==1
#include "compat/mpich1.h"
#elif defined(LAM_MPI)
#include "compat/lammpi.h"
#endif

/* ---------------------------------------------------------------- */

#if PY_MAJOR_VERSION >= 3
static PyObject * PyBuffer_FromReadWriteMemory(void *p, Py_ssize_t n) 
{
  Py_buffer info;
  if (PyBuffer_FillInfo(&info, p, n, 0, PyBUF_SIMPLE) < 0)
    return NULL;
  return PyMemoryView_FromMemory(&info);
}
#endif

#if PY_MAJOR_VERSION < 3
static char * PyMPIString_AsStringAndSize(PyObject *ob, Py_ssize_t *n) 
{
  char *s = 0;
  if (PyString_AsStringAndSize(ob, &s, n) < 0) return NULL;
  return s;
}
#define PyMPIString_AsString          PyString_AsString
#define PyMPIString_FromStringAndSize PyString_FromStringAndSize
#define PyMPIString_FromString        PyString_FromString
#else
#define PyMPIString_AsStringAndSize   PyUnicode_AsStringAndSize
#define PyMPIString_AsString          PyUnicode_AsString
#define PyMPIString_FromStringAndSize PyUnicode_FromStringAndSize
#define PyMPIString_FromString        PyUnicode_FromString
#endif

/* ---------------------------------------------------------------- */

static PyObject * PyMPI_Get_vendor(void)
{
  const char* name = "unknown";
  int major = 0;
  int minor = 0;
  int micro = 0;

  /* MPICH2 */
#if defined(MPICH_NAME) && MPICH_NAME==2
  name = "MPICH2";
  #if defined(MPICH2_VERSION)
  sscanf(MPICH2_VERSION,"%d.%d.%d",&major,&minor,&micro);
  #endif
#endif

  /* Open MPI */
#if defined(OPEN_MPI)
  name = "Open MPI";
  #if defined(OMPI_MAJOR_VERSION)
  major = OMPI_MAJOR_VERSION;
  #endif
  #if defined(OMPI_MINOR_VERSION)
  minor = OMPI_MINOR_VERSION;
  #endif
  #if defined(OMPI_RELEASE_VERSION)
  micro = OMPI_RELEASE_VERSION;
  #endif
#endif

  /* HP MPI */
#if defined(HP_MPI)
  name = "HP MPI";
  major = HP_MPI/100;
  minor = HP_MPI%100;
  #if defined(HP_MPI_MINOR)
  micro = HP_MPI_MINOR;
  #endif
#endif

  /* DeinoMPI */
#if defined(DEINO_MPI)
  name = "DeinoMPI";
#endif

  /* MPICH1 */
#if defined(MPICH_NAME) && MPICH_NAME==1
  name = "MPICH1";
  #if defined(MPICH_VERSION)
  sscanf(MPICH_VERSION,"%d.%d.%d",&major,&minor,&micro);
  #endif
#endif

  /* LAM/MPI */
#if defined(LAM_MPI)
  name = "LAM/MPI";
  #if defined(LAM_MAJOR_VERSION)
  major = LAM_MAJOR_VERSION;
  #endif
  #if defined(LAM_MINOR_VERSION)
  minor = LAM_MINOR_VERSION;
  #endif
  #if defined(LAM_RELEASE_VERSION)
  micro = LAM_RELEASE_VERSION;
  #endif
#endif

  return Py_BuildValue("s(iii)", name, major, minor, micro);

}

/* ---------------------------------------------------------------- */