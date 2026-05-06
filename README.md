<div align="center">

# scop

> A lightweight `.obj` viewer built in C++/OpenGL — loads a Wavefront model, displays it in real time, and supports multiple rendering modes, auto-rotation, and free-look camera movement.

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue) ![OpenGL](https://img.shields.io/badge/OpenGL-3.3-green) ![GLFW](https://img.shields.io/badge/GLFW-3-orange) ![Linux](https://img.shields.io/badge/platform-Linux-lightgrey)

</div>

---

## Features

- **OBJ parsing** via an internal `objParser/` library — converts geometry to triangles, falls back to per-face normals when vertex normals are missing
- **3 render modes** with smooth transitions between them:
  - `COLORED` — per-triangle color based on primitive ID
  - `SMOOTH` — per-vertex color interpolated from position direction
  - `IMAGE` — triplanar BMP texture mapping (default: `textures/comete.bmp`)
- **Free-look camera** — WASD movement, mouse look with capture toggle, scroll-wheel FOV zoom, sprint modifier
- **Auto-rotation** — pause, adjust speed, and reverse direction on the fly

---

## Prerequisites

- Linux
- A C++20 compiler (`g++` / `clang++`)
- Make
- GLFW + OpenGL

---

## Build

```bash
git clone https://github.com/Anicet78/scop.git
cd scop
make
```

---

## Usage

Pass exactly one `.obj` file as argument:

```bash
./scop path/to/model.obj
```

Example:

```bash
./scop scenes/Car.obj
```

---

## Controls

### General

| Action | Key |
|--------|-----|
| Quit | `Esc` |

### Camera movement

| Action | Key |
|--------|-----|
| Forward / Back | `W` / `S` |
| Strafe left / Right | `A` / `D` |
| Up / Down | `Space` / `L-Shift` |
| Sprint | `L-Ctrl` (hold) |
| FOV zoom | Scroll wheel |

### Mouse

| Action | Key |
|--------|-----|
| Toggle mouse capture | `R-Alt` |
| Look around | Mouse (when captured) |

### Render mode

| Action | Key |
|--------|-----|
| Cycle modes (`COLORED` → `SMOOTH` → `IMAGE`) | `Tab` |

### Auto-rotation

| Action | Key |
|--------|-----|
| Pause / Resume | `L-Alt` |
| Speed up / Slow down | `↑` / `↓` |
| Reverse direction | `←` / `→` |

---

## Project structure

```
.
├── srcs/
│   ├── openGL/          # OpenGL/GLFW wrapper, shaders (GLSL), camera
│   └── ...              # main loop, setup, model loading
├── objParser/           # OBJ/MTL parsing library (builds libobjparser.a)
├── headers/             # Math utilities (vec/mat), wrappers
└── textures/            # BMP textures used in IMAGE mode
```

> **Window settings:** maximized on startup, resizable, MSAA ×4, depth test enabled.
> Shaders are loaded from `srcs/openGL/VertexShader.glsl` and `srcs/openGL/FragmentShader.glsl`.
> GLAD is vendored; GLFW is linked as a system library.
