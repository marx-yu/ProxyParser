// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// ICU integration functions.

#include <stdlib.h>
#include <string.h>

//#include "third_party/icu/source/common/unicode/ucnv.h"
//#include "third_party/icu/source/common/unicode/ucnv_cb.h"
//#include "third_party/icu/source/common/unicode/uidna.h"
#include "url/url_canon_icu.h"
#include "url/url_canon_internal.h"  // for _itoa_s

namespace url {




// Converts the Unicode input representing a hostname to ASCII using IDN rules.
// The output must be ASCII, but is represented as wide characters.
//
// On success, the output will be filled with the ASCII host name and it will
// return true. Unlike most other canonicalization functions, this assumes that
// the output is empty. The beginning of the host will be at offset 0, and
// the length of the output will be set to the length of the new host name.
//
// On error, this will return false. The output in this case is undefined.
// TODO(jungshik): use UTF-8/ASCII version of nameToASCII.
// Change the function signature and callers accordingly to avoid unnecessary
// conversions in our code. In addition, consider using icu::IDNA's UTF-8/ASCII
// version with StringByteSink. That way, we can avoid C wrappers and additional
// string conversion.
bool IDNToASCII(const base::char16* src, int src_len, CanonOutputW* output) {
  //DCHECK(output->length() == 0);  // Output buffer is assumed empty.

  //UIDNA* uidna = g_uidna.Get().value;
  //DCHECK(uidna != NULL);
  //while (true) {
  //  UErrorCode err = U_ZERO_ERROR;
  //  UIDNAInfo info = UIDNA_INFO_INITIALIZER;
  //  int output_length = uidna_nameToASCII(uidna, src, src_len, output->data(),
  //                                        output->capacity(), &info, &err);
  //  if (U_SUCCESS(err) && info.errors == 0) {
  //    output->set_length(output_length);
  //    return true;
  //  }

  //  // TODO(jungshik): Look at info.errors to handle them case-by-case basis
  //  // if necessary.
  //  if (err != U_BUFFER_OVERFLOW_ERROR || info.errors != 0)
  //    return false;  // Unknown error, give up.

  //  // Not enough room in our buffer, expand.
  //  output->Resize(output_length);
  //}

	return false;
}

}  // namespace url
