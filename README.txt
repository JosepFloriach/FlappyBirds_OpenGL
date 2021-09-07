===========================================================================================
=================================== ZEPTOLAB APPLY TEST by JOSEP FLORIACH VENTOSINOS=======
===========================================================================================
This document intention is to explain the decisions I took while I was implementing the Flappy Birds test to apply to Zeptolab position.

======================================================= INTRODUCTION ======================
In first place, and as you will see, I developed a (very) minimalistic engine. This engine can draw graphics, build a scene, and deal with physics.

I decided to implement my own engine due the fact that even if it was a very simple game, the truth is that I found myself designing several diferent classes for different purposes. And I thought that taking advantage of this, why do not implement a minimalistic engine? In this way the build of flappy birds game would be so much easy and straight forward. Besides, I would test each funcionality more comfortable. The engine is pretty much based in Unity workflow. An entity-component system.

There is a known bug in which in lower resolution devices the main menu interface is broken and some text views and buttons overlaps. I didn't give much priority because I think it's a matter of UI well-design.

When you open the App, you will see several buttons and sliders. The main button is Flappy Birds under the title ZEPTOLAB TEST. This button will took you to the actual game of Flappy Birds. Below that, you will see several buttons that will take you to different scenes. These scenes are built to perform some "unit testing" through the different functionalities of the engine. Each of this scene will test a specific functionality (i.e. Draw geometric shapes, or another one to test the collisions between them). Finally, below this test scenes, you will notice different sliders. These sliders are to setup the Flappy Birds game parameters. I made this in this way to help myself to 
find the optimal parameters in which I had a satisfactory feeling playing the game.

======================================================= TECHNICAL KEY POINTS ================
The rules for the test were that it had to be implemented in OpenGL 2.0 without the help of any kind engine, and from NDK using a simple java interface. There are some programming techniques I used, that I think they are worth to be explained.

- Pointer to implementation (PIMPL idiom): 	I used this programming technique in some places in the code. I think it's a great techinque to avoid long-compiling times, and to hide implementation data from the client. Moreover, I used in classes which I think had the potential to be improved or to grown in size.

- Strong types: Strong types (I'm not sure that this is the official name) are types that helps the code to be more readable. For example, instead of using a float to define the width of a square, I think it's much better to use a trivial type named "Width". Used in funciton parameters, the user knows inmediatly that the first parameter of a specific function is to define the Width, and the second one, to define the Height. So much more readable than just defining the function with two floats.
											
- Scene testing	: As I explained before, the testing scenes have been built to perform some "Unit testing" over the development proccess. Is an easy way to check that a new funcionality does not broke an older one.
											
- CRTP: CRTP is a metaprogramming technique useful to avoid the cost of virtual functions, if there is no dynamic polymorphism in a specifi class. Transform class is a very basic CRTP, and is used by SceneNode and Component to add transform funcionalities to the scene. A potential improvement would be to create another CRTP to the hierarchy of components Renderer/ShapeRenderer, since they are not used for dynamic polymorphism.

- Transform: Allowed transforms are Translation, Scale and Rotation. There are three different contexts in which a transform can be applied. Absolute coordinates (taking the center of the world as reference, relative coordinates (taking the parent of transform as coordinate), and local coordinates (taking the center of the own object as reference). However, and for simplicity, I've decided to not apply absolute Scalations. Scale transform can just be applied locally or relatively, so the scale reference will be always the center of the object, or relative to the parent transform.

- WHERE IS THE FLAPPY GAME SCORE???: The main problem with the score is that it has to be implemented in one of the following ways: with OpenGL, or with Android TextView widget into the activity. The problem with the last one is that it has an overhead due the communication between NDK and Java, and the score has to be updated in every frame (maybe with event polling would reduce this overhead). I haven't implemented the OpenGL way due the lack of time.
											
======================================================= POTENTIAL IMPROVEMENTS  ==========
I tried to develop the engine in a flexible way, so it could be easy to implement new functionalities and improvements. For lack of time there are so many things I've decided to do for the future. I'll try to explain some of the potential improvements.

- Fix the Main Game Activity resolution: In some devices with lower resolutions, the main game Activity is not shown correctly. I must fix it.

- Physics response : Apply physics response when to physic bodies collides between them. This would fix the problem of trapassing walls that happens right now in the Flappy birds game (although I think it looks good).

- Text rendering!!!: Text rendering with OpenGL would suppose a wonderful improvement for the engine. It would allow to implement score in the Flappy Birds game, without having the communication overhead between Java and NDK.

- Shader loading: I found a lack of documentation relative to load resources in Android from NDK. Since I though this was not the point of the project, I' ve decied to load them directly from code. In fact, there is just one shader right now. The default one, that load the transformation matrices. I potential improvement would be to load them from .frag and .vert files.
										
- Textures, and materials: I've developed the whole project with geometric shapes drawn directly from OpenGL. A potential improvement would be to have the ability to draw textures/sprites and materials from shaders. They are more efficient than drawing from OpenGL primitives.

- Rotations from a specific center: All current rotations are relative to the world center or to the object center. It would be nice to specify a rotation point.

- Improve the app usability: I'm not an experienced UI designer, but I think the current layout for the application is pretty ugly. Also, it would be nice to put all setup parameters of the Flappy Bird game into another activity, so they can be independent from the testing scenes. Another one. Put a restart button to the Flappy Birds game. It's pretty uncomfortable to have to press back-button and Flappy Birds button to restart the game.

- Allow component transformations: Right now, the components have the position, scale and rotation bind to them nodes. They should have their own transformation so for example you can apply a little offset from the node, to a Box Collider.

- Quadtree for the collisions system: The current system collision check every pair of objects in the scene. This is extremely bad for performance. A very good improvement would be to implement a Quadtree to just check collisions between nodes that they are close to each other.

- Add more touch events: Right now it's just the touch-down event. The engine would be responsive to pinch-touch, to finger-move...

======================================================= INTO THE FUTURE!!!!  =========
The following things are improvements to the long term.

- Visual tool to design scenes: And they are loaded into the engine through XML's files generated by the own tool.

- 3D models rendering: It would be nice.	

- Flightweight pattern: To performance matters. To achieve this the engine should use OpenGL 3.0 to allow instanced rendering.

- Fixed delta time: To avoid differentes in physics system between devices, when they are running at low frame rate.

- More versatile collisions: Right now, I cannot detect collisions of objects non-axis-aligned. I should implement some more powerful collision algorithm like Separation Axis Theorem.
											
