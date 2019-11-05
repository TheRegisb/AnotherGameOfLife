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

#include "GameOfLife/Parameters.hpp"

agof::Parameters::Parameters(): width(DEFAULT_WIDTH), height(DEFAULT_HEIGHT), nox(false)
{

}

void agof::Parameters::setWidth(const char *str)
{
	if (str == nullptr) {
		throw std::invalid_argument("Width is null.");
	}
	
	int width = std::atoi(str);

	if (width <= 0) {
		throw std::invalid_argument("Width cannot be negative or equal to zero.");
	}
	setWidth(width);
}

void agof::Parameters::setWidth(unsigned int width)
{
	if (width == 0) {
		throw std::invalid_argument("Width cannot be equal to zero.");
	}
	this->width = width;
}

void agof::Parameters::setHeight(const char *str)
{
	if (str == nullptr) {
		throw std::invalid_argument("Height is null.");
	}

	int height = std::atoi(str);

	if (height <= 0) {
		throw std::invalid_argument("Height cannot be negative or equal to zero.");
	}
	setHeight(height);
}

void agof::Parameters::setHeight(unsigned int height)
{
	if (height == 0) {
		throw std::invalid_argument("Height cannot be equal to zero.");
	}
	this->height = height;
}

unsigned int agof::Parameters::getWidth() const
{
	return width;
}

unsigned int agof::Parameters::getHeight() const
{
	return height;
}

void agof::Parameters::setNox(bool nox)
{
  this->nox = nox;
}

bool agof::Parameters::isNox() const
{
  return nox;
}
