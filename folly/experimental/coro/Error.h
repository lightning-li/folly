/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <type_traits>

#include <folly/ExceptionWrapper.h>

namespace folly {
namespace coro {

class co_error {
 public:
  template <
      typename... A,
      std::enable_if_t<
          sizeof...(A) && std::is_constructible<exception_wrapper, A...>::value,
          int> = 0>
  explicit co_error(A&&... a) noexcept(
      std::is_nothrow_constructible<exception_wrapper, A...>::value)
      : ex_(static_cast<A&&>(a)...) {}

  const exception_wrapper& exception() const {
    return ex_;
  }

  exception_wrapper& exception() {
    return ex_;
  }

 private:
  exception_wrapper ex_;
};

} // namespace coro
} // namespace folly
