## Development Environment Setup

### IntelliSense Configuration
`.vscode/c_cpp_properties.json` is excluded from version control as it contains
machine-specific paths. To generate it locally:

1. Open the project in VS Code
2. Ensure the Silicon Labs board core is installed via Board Manager
3. Open `home_temperature_system.ino`
4. Run `Arduino: Rebuild IntelliSense Configuration` from the Command Palette
5. Select **Nano Matter** as the target board

> TODO: Replace hardcoded paths with environment variables and commit
> `c_cpp_properties.json` to version control.

### CMake Presets
`CMakePresets.json` is excluded from version control as it contains
machine-specific paths. To configure CMake locally:

1. Install CMake and Visual Studio Build Tools 2022 (Desktop development with C++)
2. Recreate `CMakePresets.json` with your local paths
3. Select the **MSVC** preset via `CMake: Select Configure Preset`

> TODO: Replace hardcoded paths with environment variables and commit
> `CMakePresets.json` to version control.# home_temperature_system