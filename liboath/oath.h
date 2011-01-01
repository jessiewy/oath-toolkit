/*
 * oath.h - header file for liboath
 * Copyright (C) 2009, 2010, 2011 Simon Josefsson
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#ifndef OATH_H
# define OATH_H

# ifndef OATHAPI
#  if defined LIBOATH_BUILDING && defined HAVE_VISIBILITY && HAVE_VISIBILITY
#   define OATHAPI __attribute__((__visibility__("default")))
#  elif defined LIBOATH_BUILDING && defined _MSC_VER && ! defined LIBOATH_STATIC
#   define OATHAPI __declspec(dllexport)
#  elif defined _MSC_VER && ! defined LIBOATH_STATIC
#   define OATHAPI __declspec(dllimport)
#  else
#   define OATHAPI
#  endif
# endif

#include <stdbool.h>		/* For bool. */
#include <stdint.h>		/* For uint64_t, SIZE_MAX. */
#include <string.h>		/* For size_t.t */
#include <time.h>		/* For time_t. */

/**
 * OATH_VERSION
 *
 * Pre-processor symbol with a string that describe the header file
 * version number.  Used together with oath_check_version() to verify
 * header file and run-time library consistency.
 */
# define OATH_VERSION "1.2.2"

/**
 * OATH_VERSION_NUMBER
 *
 * Pre-processor symbol with a hexadecimal value describing the
 * header file version number.  For example, when the header version
 * is 1.2.3 this symbol will have the value 0x010203.
 */
# define OATH_VERSION_NUMBER 0x010202

/**
 * oath_rc:
 * @OATH_OK: Successful return
 * @OATH_CRYPTO_ERROR: Internal error in crypto functions
 * @OATH_INVALID_DIGITS: Unsupported number of OTP digits
 * @OATH_PRINTF_ERROR: Error from system printf call
 * @OATH_INVALID_HEX: Hex string is invalid
 * @OATH_TOO_SMALL_BUFFER: The output buffer is too small
 * @OATH_INVALID_OTP: The OTP is not valid
 * @OATH_REPLAYED_OTP: The OTP has been replayed
 * @OATH_BAD_PASSWORD: The password does not match
 * @OATH_INVALID_COUNTER: The counter value is corrupt
 * @OATH_INVALID_TIMESTAMP: The timestamp is corrupt
 * @OATH_NO_SUCH_FILE: The supplied filename does not exist
 * @OATH_UNKNOWN_USER: Cannot find information about user
 * @OATH_FILE_SEEK_ERROR: System error when seeking in file
 * @OATH_FILE_CREATE_ERROR: System error when creating file
 * @OATH_FILE_LOCK_ERROR: System error when locking file
 * @OATH_FILE_RENAME_ERROR: System error when renaming file
 * @OATH_FILE_UNLINK_ERROR: System error when removing file
 * @OATH_TIME_ERROR: System error for time manipulation
 *
 * Return codes for OATH functions.  All return codes are negative
 * except for the successful code OATH_OK which are guaranteed to be
 * 0.  Positive values are reserved for non-error return codes.
 *
 * Note that the #oath_rc enumeration may be extended at a later date
 * to include new return codes.
 */
typedef enum
{
  OATH_OK = 0,
  OATH_CRYPTO_ERROR = -1,
  OATH_INVALID_DIGITS = -2,
  OATH_PRINTF_ERROR = -3,
  OATH_INVALID_HEX = -4,
  OATH_TOO_SMALL_BUFFER = -5,
  OATH_INVALID_OTP = -6,
  OATH_REPLAYED_OTP = -7,
  OATH_BAD_PASSWORD = -8,
  OATH_INVALID_COUNTER = -9,
  OATH_INVALID_TIMESTAMP = -10,
  OATH_NO_SUCH_FILE = -11,
  OATH_UNKNOWN_USER = -12,
  OATH_FILE_SEEK_ERROR = -13,
  OATH_FILE_CREATE_ERROR = -14,
  OATH_FILE_LOCK_ERROR = -15,
  OATH_FILE_RENAME_ERROR = -16,
  OATH_FILE_UNLINK_ERROR = -17,
  OATH_TIME_ERROR = -18,
} oath_rc;

/* Global */

extern OATHAPI int oath_init (void);
extern OATHAPI int oath_done (void);

extern OATHAPI const char *oath_check_version (const char *req_version);

extern OATHAPI int oath_hex2bin (char *hexstr, char *binstr, size_t * binlen);

/* HOTP */

#define OATH_HOTP_LENGTH(digits, checksum) (digits + (checksum ? 1 : 0))

#define OATH_HOTP_DYNAMIC_TRUNCATION SIZE_MAX

extern OATHAPI int oath_hotp_generate (const char *secret,
				       size_t secret_length,
				       uint64_t moving_factor,
				       unsigned digits,
				       bool add_checksum,
				       size_t truncation_offset,
				       char *output_otp);


extern OATHAPI int oath_hotp_validate (const char *secret,
				       size_t secret_length,
				       uint64_t start_moving_factor,
				       size_t window, const char *otp);

/* Usersfile */

extern OATHAPI int oath_authenticate_usersfile (const char *usersfile,
						const char *username,
						const char *otp,
						size_t window,
						const char *passwd,
						time_t * last_otp);

#endif /* OATH_H */