# RLBotCPP

C++ client for the [RLBot framework](https://github.com/RLBot/RLBot).

## How to use:
- Use cmake to generate the solution.
- Build the executable.
- Copy the latest dll files from the RLBot pip package to the executable folder.
- Start a Rocket League match by running `dev/run.bat`.
- Start the C++ bot executable.

## Release version:
To share your bot you will need to create a bot that is automatically launched by the framework.
 - Copy your C++ bot executable to `release/`.
 - Make sure that the `path` field in `release/CppPythonAgent.cfg` points to your C++ bot executable.
 - Make sure that the `python_file` field in `release/CppPythonAgent.cfg` points to the python agent executable.
 
### Notes:
When your bot is started by the RLBot match runner it will not be able to use relative file paths.
