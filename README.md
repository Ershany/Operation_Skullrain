# Operation Skullrain
A Helicopter Shooter game created in C++ and OpenGL. Based on the Arcane Engine

![Operation Skullrain](https://cdn.discordapp.com/attachments/357967475276775424/389628249543671811/unknown.png)

## About
This game was created for third-year game development at Carleton University. It can be run using Visual Studio 2013+ without the need to install any extra libraries.

## Required Features
- General Fire (Enemy): Only implemented for the player death animation. The flames will spread upon the player’s death from the enemies (or you can hold k to kill yourself in-game)
- Projectiles (Enemy): Projectiles will fire from randomly spawning towers around the terrain. The projectiles will damage the play if they don’t either dodge them, blow them up or have their invincible shield on.
- NPC’s (Obstacle): NPC’s will randomly spawn around the map. They will walk toward your helicopter when they are within a certain radius around the helicopter. When they get close to the helicopter they will go inside of the helicopter and you can view them in first - person mode.
- Water Gun (Weapon): The player can press 1 for the primary weapon fire. It has a 5 second cooldown after it is used, and will fire for 2 seconds. It is designed to be used against towers and other projectiles.
Invincibility Bubble (Weapon): The invincibility bubble appears as a ‘skin’ surrounding the helicopter using the renderer’s light refraction. No projectiles can hit the heli whilst active.
- Free-flying Helicopter: Helicopter flight programmed on 3-axis. Has the feel of a real-life helicopter as accelerating tilts the heli forwards and vice - versa for decelerating.
- Third & First Person: Being able to switch seamlessly between third and first person view is achieved by a boolean value on the camera object. If third person is true, the camera position simply shifts outside of the helicopter.
- Collision detection: The helicopter currently collides with the terrain (which isn’t flat but instead it uses a heightmap). It also collides with NPCs and they will even approach you once you get close enough.
- Hierarchical rotation of the rotor blades and turrets on helicopter. Using quaternions and a local hierarchical scene-graph adaption.
- Lighting Blinn-Phong lighting algorithm. With support for point lights, spotlights and directional lights. (all showcased within the game)
- Cubemap Support: Custom shader to render skybox with.

## Additional Features
- Support for loading models and their materials (diffuse maps, specular maps)
- Framebuffer creation with post processing capabilities (not in use, but is there if needed, we have the shaders and render pass already occurring, we just aren’t applying a convolution matrix) Our framebuffer also supports MSAA and will blit the multisampled framebuffer to a non-multisampled buffer so we can perform post processing
- Terrain rendering that supports multi-texturing (up to 5 textures: using a blend-map). And uses a heightmap to achieve proper hills and valleys.
- Basic Blending support, and the renderer will handle transparent objects by disabling back face culling and rendering back to front.
- Fullscreen support
- Shaders for reflection and refraction using our skybox cubemap (basic environment map)
- MSAA support (Multi-sample anti-aliasing)
- Anisotropic filtering support, this greatly increases the quality of the terrain
- Simple 2D UI

## Features Not Implemented
- General flame algorithm
- Burning trees
- Spreading fire algorithm
- City drop point
- City Model
- Refueling
- Water refueling
- Fuel refueling
- Weapon collision detection
- Between weapon projectiles and enemy projectiles
- Between weapon projectiles and towers

## Arcane Engine
3D C++ Game Engine - Created By Brady Jessup
![arcaneengine](https://user-images.githubusercontent.com/11170417/27188219-75d8814e-51bb-11e7-907b-1be35da8de38.png)
Arcane Engine uses:
- OpenGL (Graphics API)
- GLFW (Window/Input callback handling)
- GLEW (Allows me to use modern versions of OpenGL)
- GLM (Math library for OpenGL)
- SOIL (Image loader)
- Assimp (Model/Scene loader)
- FreeType and FreeType-GL (Text Rendering)