#ifndef PyMPI_COMPAT_MPICH3_H
#define PyMPI_COMPAT_MPICH3_H

#if defined(MPICH_NUMVERSION)
#if (MPICH_NUMVERSION < 30100000)

static int PyMPI_MPICH3_MPI_Type_size_x(MPI_Datatype datatype, MPI_Count *size)
{
  int ierr = MPI_Type_commit(&datatype); if (ierr) return ierr;
  return MPI_Type_size_x(datatype,size);
}
#undef  MPI_Type_size_x
#define MPI_Type_size_x PyMPI_MPICH3_MPI_Type_size_x

static int PyMPI_MPICH3_MPI_Type_get_extent_x(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent)
{
  int ierr = MPI_Type_commit(&datatype); if (ierr) return ierr;
  return MPI_Type_get_extent_x(datatype,lb,extent);
}
#undef  MPI_Type_get_extent_x
#define MPI_Type_get_extent_x PyMPI_MPICH3_MPI_Type_get_extent_x

static int PyMPI_MPICH3_MPI_Type_get_true_extent_x(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent)
{
  int ierr = MPI_Type_commit(&datatype); if (ierr) return ierr;
  return MPI_Type_get_true_extent_x(datatype,lb,extent);
}
#undef  MPI_Type_get_true_extent_x
#define MPI_Type_get_true_extent_x PyMPI_MPICH3_MPI_Type_get_true_extent_x

static int PyMPI_MPICH3_MPI_Get_accumulate(const void *origin_addr, int origin_count,
                                           MPI_Datatype origin_datatype, void *result_addr, int result_count,
                                           MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp,
                                           int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
  double origin_buf, result_buf;
  if (!origin_addr && !origin_count) origin_addr = (const void *)&origin_buf;
  if (!result_addr && !result_count) result_addr = (void *)&result_buf;
  return MPI_Get_accumulate(origin_addr, origin_count, origin_datatype,
                            result_addr, result_count, result_datatype,
                            target_rank,
                            target_disp, target_count, target_datatype,
                            op, win);
}
#undef  MPI_Get_accumulate
#define MPI_Get_accumulate PyMPI_MPICH3_MPI_Get_accumulate

static int PyMPI_MPICH3_MPI_Rget_accumulate(const void *origin_addr, int origin_count,
                                            MPI_Datatype origin_datatype, void *result_addr, int result_count,
                                            MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp,
                                            int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win,
                                            MPI_Request *request)
{
  double origin_buf, result_buf;
  if (!origin_addr && !origin_count) origin_addr = (const void *)&origin_buf;
  if (!result_addr && !result_count) result_addr = (void *)&result_buf;
  return MPI_Rget_accumulate(origin_addr, origin_count, origin_datatype,
                             result_addr, result_count, result_datatype,
                             target_rank,
                             target_disp, target_count, target_datatype,
                             op, win, request);
}
#undef  MPI_Rget_accumulate
#define MPI_Rget_accumulate PyMPI_MPICH3_MPI_Rget_accumulate

#endif
#endif

#endif /* !PyMPI_COMPAT_MPICH3_H */
