This is an opensource cnc cam software used to compute toolpath and generate gcode or whatever. You can import DXF, or directly draw using the tools available.

Postprocessors are written in python.

The code is written in c++/20 using Visual Studio 22.

Display is done with OpenGL 3, using third parties (gl3w, glfw, glm).
UI is performed by Dear ImGUI.
Fonts are managed using Freetype.

To run it, you need to install Python 3.13 runtime and Visual C++/64 runtime.

Compilation will run copy_libs_output.bat to copy libs folders into bin directory : fonts, lang, postpro, script, textures, src/shaders

Languages for UI are managed through language files located in /lang with a pair of key=value

This is the first early release. The algorithm for outlines needs lots of improvments, such as changing from float to double.

It should be able to compile for Linux or Mac. Really few things are Windows OS dependant. Not tested yet.

![openpostpro](https://github.com/user-attachments/assets/fc224d77-bbef-4d37-98aa-c54a5e4b89e1)

I had great fun in writting it, I hope you enjoyed it.

Feel free to write to me : thomas.gourgnier@live.fr
