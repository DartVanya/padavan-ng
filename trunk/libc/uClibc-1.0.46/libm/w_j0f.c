/* Copyright (C) 2011-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gmail.com>, 2011.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <math.h>
#include "math_private.h"
#if defined(__UCLIBC_HAS_FENV__)
#include <fenv.h>
#endif

#ifndef __DO_XSI_MATH__
/* wrapper j0f */
float
j0f (float x)
{
# if defined(__UCLIBC_HAS_FENV__)
  if (__builtin_expect (isgreater (fabsf (x), (float) X_TLOSS), 0)
      && _LIB_VERSION != _IEEE_ && _LIB_VERSION != _POSIX_)
    /* j0(|x|>X_TLOSS) */
    return __kernel_standard_f (x, x, 134);
# endif /* __UCLIBC_HAS_FENV__ */
  return (float) __ieee754_j0 ((double) x);
}


/* wrapper y0f */
float
y0f (float x)
{
# if defined(__UCLIBC_HAS_FENV__)
  if (__builtin_expect (islessequal (x, 0.0f)
                        || isgreater (x, (float) X_TLOSS), 0)
      && _LIB_VERSION != _IEEE_)
    {
      if (x < 0.0f)
	{
	  /* d = zero/(x-x) */
	  feraiseexcept (FE_INVALID);
	  return __kernel_standard_f (x, x, 109);
	}
      else if (x == 0.0f)
	{
	  /* d = -one/(x-x) */
	  feraiseexcept (FE_DIVBYZERO);
	  return __kernel_standard_f (x, x, 108);
	}
      else if (_LIB_VERSION != _POSIX_)
	/* y0(x>X_TLOSS) */
	return __kernel_standard_f (x, x, 135);
    }
# endif /* __UCLIBC_HAS_FENV__ */
  return (float) __ieee754_y0 ((double) x);
}
#endif /* __DO_XSI_MATH__ */
