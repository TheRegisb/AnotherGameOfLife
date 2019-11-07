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

/**
 * @file Parameters.hpp
 * Singleton managing global game parameters.
 */
#pragma once

#include <stdexcept>
#include <cstdlib>

constexpr unsigned int DEFAULT_HEIGHT = 50;
constexpr unsigned int DEFAULT_WIDTH = 50;

namespace agof {

  /**
   * Singleton managing global game parameters.
   * This class is intended to store and make available globally
   * several parameters for the life time of the instance.
   * This class cannot be instances.
   */
	class Parameters {
	public:
	  /**
	   * Get the singleton.
	   */
		static Parameters &get() {
			static Parameters singleton;

			return singleton;
		}

	  /**
	   * Set the width of the board.
	   * Set the width of the board to be used during the game
	   * by converting an unsigned number litteral to its numeric value.
	   * @param str Unsigned number litteral.
	   * @throws invalid_argument on null, non-numeric or zero or lesser value.
	   */
		void setWidth(const char *str);
	  /**
	   * Set the width of the board.
	   * Set the width of the board to be used during the game.
	   * @param width A greater than zero value.
	   * @throws invalid_argument on equal or lesser than zero value.
	   */
		void setWidth(unsigned int width);
	  /**
	   * Set the height of the board.
	   * Set the height of the board to be used during the game
	   * by converting an unsigned number litteral into its numeric value.
	   * @param str Unsigned number litteral.
	   * @thows invalid_argument on null, non-numeric or zero or lesser value.
	   */
		void setHeight(const char *str);
	  /**
	   * Set the height of the board.
	   * Set the height of the board to used during the game.
	   * @param height A greater than zero value.
	   * @throws invalid_agument on equal or lesser than zero value.
	   */
		void setHeight(unsigned int height);
	  /**
	   * Raises the No-X display mode flag.
	   */
		void setNox(bool nox);

	  /**
	   * Get the stored width.
	   * @return Width of the board.
	   */
		unsigned int getWidth() const;
	  /**
	   * Get the stored height.
	   * @return Height of the board.
	   */
		unsigned int getHeight() const;
	  /**
	   * Get the No-X display mode flag.
	   * @return The No-X display mode flag.
	   */
		bool isNox() const;

	private:
	  /* Prevents singleton duplication or copy. */
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
