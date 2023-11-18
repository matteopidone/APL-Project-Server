# Project - Advanced Programming Languages
# Server - C++ - Drogon Framework

Server developed using the `Drogon` framework in `C++`.<br>
Drogon Framework GitHub Repository: <a href="https://github.com/drogonframework/drogon" target="_blank">click here</a><br>
All classes used within the project are divided into two files:
- `.h` file, for function definitions
- `.cc` file, for function implementations

# Installation and Usage
To use the server, Docker is required.<br>
After cloning the repository, execute the following commands within the project directory:
```bash
mkdir mysql_data
docker compose up
```
This will create two containers.<br>
In the first container, framework dependencies will be installed, the project will be compiled, and then executed.<br>
In the second container, the `mysql` database will be installed with a corresponding dump. This way, some project-related data will already be available.

# Project Structure
The entry point of the project is the `main.cc` file.<br>
Here, the `config.json` configuration file is loaded at runtime, and the server is instantiated.

The main directories are:
- `controllers` -> controllers defining the server's `endpoints`
- `models` -> models related to the involved data structures
- `plugins` -> additional project functionalities

## Controllers
In the `controllers` directory, two classes extend the `HttpController` and `Utility` (see plugins) classes.<br>
The `HttpController` class is a Drogon Framework class that allows associating functions with endpoints.<br>
The classes in question are:
- `UserController`, functionality related to users
- `HolidayController`, functionality related to holidays

## Models
In the `models` directory, two classes offer a series of functionalities for data manipulation and database access.<br>
The classes are:
- `User`, for user management
- `Holiday`, for holiday management

## Plugins
In the `plugins` directory, two classes manage additional functionalities.<br>
The classes are:
- `jwt`, for authentication management using `Json Web Token`
- `utility`, for managing additional common-use functionalities and controls

There is also a `constants.h` file, where constants used in defining endpoints are defined.
