// Copyright 2019 Régis Berthelot

// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <stdexcept>
#include <cstdlib>

constexpr unsigned int DEFAULT_HEIGHT = 50;
constexpr unsigned int DEFAULT_WIDTH = 50;

namespace agof {

	class Parameters {
	public:
		static Parameters &get() {
			static Parameters singleton;

			return singleton;
		}

		void setWidth(const char *str);
		void setWidth(unsigned int width);
		void setHeight(const char *str);
		void setHeight(unsigned int height);
		void setNox(bool nox);

		unsigned int getWidth() const;
		unsigned int getHeight() const;
		bool isNox() const;

	private:
		Parameters();
		static void *operator new(size_t) = delete;
		static void *operator new[](size_t) = delete;
		static void operator delete(void *) = delete;
		static void operator delete[](void *) = delete;

		unsigned int width;
		unsigned int height;
		bool nox;
	};
}
