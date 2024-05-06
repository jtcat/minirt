# MiniRT - A 42 School Ray Tracer
This is a simple software ray tracer written in C.
# Authorship
João Catarino: [@jtcat](https://github.com/jtcat)

Pedro Souto: [@peterbikes](https://github.com/peterbikes)
# Features
- Scene description via file
- Phong shading
- Hard shadows
- Three primitive types: planes, spheres and cylinders
- Ambient lighting
- Support for multiple colored point-lights
- Transform based object translation and rotation
- Real-time scene editing
# Building
This project requires the 42 School [minilibx](https://github.com/42Paris/minilibx-linux) library to be present at the root of the project.
Then simply run `make`
# Usage
MiniRT requires a scene description file with an `.rt` extension.

This snippet represents a simple configuration with all possible primitive types:
```
A 0.2    255,255,255
C 130,0,0    0,0,-1    70
L 130,0,-50    0.7    255,255,255
pl 0,-60,0    0,1.0,0    255,0,225
sp 130,25,-100    20    255,0,0
cy 130,0.0,-100.6    0,1.0,0    14.2 30.42    10,0,255
```

Then simply run
`./miniRT scene.rt`
