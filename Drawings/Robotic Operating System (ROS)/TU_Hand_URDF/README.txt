The Unified Robotic Description Format (URDF), maintained by the Open Source Robotics Foundation, which evolved from Willow Garage. URDF is XML-based in its formatting, and is used in the Robotic Operating System (ROS).

	(www.ros.org)

Resource page for viewing URDF Files:

	https://docs.ros.org/en/jazzy/Tutorials/Intermediate/URDF/Exporting-an-URDF-File.html

		-Viewing URDF and SDF Files
		-Web Viewer for URDF Files: GitHub Repo & Live Website
		-hyperlink "Website": https://gkjohnson.github.io/urdf-loaders/javascript/example/bundle/index.html
		-Using Google Chrome, drag and drop the TUHand_<version>_URDF folder into the web viewer at the above link.
			-If no visible model, zoom in/out to scale the camera view via the mouse wheel.
		-The TU hand will be rendered; perspective and joint angles can be controlled by click-to-drag on bodies/background, or clicking "show controls".
		-(this is not a replacement for RViz or other ROS tutorial components, just a convenient online tool that doesn't require any ROS installed). 

					
Guidelines for further development: follow docs.ros.org guidelines, focusing on usage of Xacro, RViz, and simulators such as Gazebo. See IMG_2358.GIF and TUHand_URDF_GAZEBO.doc for initial results deploying the URDF in a physics simulation; fairly realistic inertial properties were observed under freefall and collision states.

Future Work: update TUHand model to reflect doctoral thesis; current model is based on TU Hand components prior to my dissertation at University of Tulsa.