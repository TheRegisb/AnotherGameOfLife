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

#include <iostream>
#include <cstring>

/* Compilation-unit constants. */

constexpr unsigned int VERSION_MAJOR = 1;
constexpr unsigned int VERSION_MINOR = 0;

constexpr unsigned int CODE_MESSAGE = EXIT_SUCCESS;
constexpr unsigned int CODE_INVALID = EXIT_FAILURE;
constexpr unsigned int CODE_CONTINUE = 0xC0;

/* Functions declarations. Statics for performance boost. */

static int optionsHandle(char **av);
static void displayHelp();
static void displayAbout();

int main(int ac, char **av)
{
	try {
		int optionsCode = optionsHandle(av);
		if (optionsCode != CODE_CONTINUE) {
			return optionsCode;
		}
	} catch (const std::invalid_argument &exp) {
		std::cout << av[0] << ": Invalid option: " << exp.what() << std::endl;
		return EXIT_FAILURE;
	}
	// return gameOfLife();
	return EXIT_SUCCESS;
}

static int optionsHandle(char **args)
{
	for (int i = 1; args[i] != nullptr; i++) {
		if ((strcmp(args[i], "--width") == 0 || strcmp(args[i], "-w") == 0)) {
			agof::Parameters::get().setWidth(args[i + 1]);
			i++;
		} else if (strcmp(args[i], "--height") == 0 || strcmp(args[i], "-h") == 0) {
			agof::Parameters::get().setHeight(args[i + 1]);
			i++;
		} else if (strcmp(args[i], "--help") == 0 || strcmp(args[i], "-H") == 0) {
			displayHelp();
			return CODE_MESSAGE;
		} else if (strcmp(args[i], "--about") == 0 || strcmp(args[i], "-a") == 0) {
			displayAbout();
			return CODE_MESSAGE;
		} else {
			std::cerr << args[0] << ": Unknown option: " << args[i] << std::endl;
			return CODE_INVALID;
		}
	}
	return CODE_CONTINUE;
}

static void displayHelp()
{
	std::cout << "Usage: agof [OPTIONS]" << std::endl << std::endl
		  << "OPTIONS:"
		  << std::endl
		  << "  -H, --help" << std::endl
		  << "\t\tDisplay this help message"
		  << std::endl
		  << "  -a, --about" << std::endl
		  << "\t\tDisplay version number, author and licensing"
		  << std::endl
		  << "  -h, --height X" << std::endl
		  << "\t\tHeight of the board, must be greater than zero, 50 by default"
		  << std::endl
		  << "  -w, --width Y" << std::endl
		  << "\t\tWidth of the board, must be greater than zero, 50 by default"
		  << std::endl;
}

static void displayAbout()
{
	std::cout << "Another Game of Life, "
		  << "version " << VERSION_MAJOR << "." << VERSION_MINOR
		  << ", make by Régis Berthelot, licensed under the "
		  << "Apache License version 2.0"
		  << std::endl;
}
