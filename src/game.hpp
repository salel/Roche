#pragma once

#include "graphics_api.hpp"

#include "planet.hpp"
#include "renderer.hpp"
#include <glm/glm.hpp>

#include <bitset>
#include <vector>
#include <memory>

/**
 * All application logic
 */
class Game
{
public:
	Game();
	~Game();
	/**
	 * Loads configuration files
	 */
	void init();
	/**
	 * Updates one frame
	 * @dt delta time since last frame
	 */
	void update(double dt);
	/**
	 * Indicates whether the application has been requested to stop
	 */
	bool isRunning();

private:
	/**
	 * Returns true when the key is pressed, but false when it's held
	 * @param key GLFW key to check
	 * @param whether the key is pressed but not held
	 */
	bool isPressedOnce(int key);

	/// Loads planet configuration files
	void loadPlanetFiles();
	/// Loads settings file
	void loadSettingsFile();

	/// Returns the id of planet's parent (-1 if no parent)
	int getParent(size_t planetId);
	/// Returns all parents (recursive) until there is no parent
	std::vector<size_t> getAllParents(size_t planetId);
	/// Returns the level of planet inside the hierarchy
	int getLevel(size_t planetId);
	/// Returns direct children
	std::vector<size_t> getChildren(size_t planetId);
	/// Returns all children recursively
	std::vector<size_t> getAllChildren(size_t planetId);

	/// Returns planets in the vicinity of the given planet
	std::vector<size_t> getFocusedPlanets(size_t focusedPlanetId);

	/// Renderer
	std::unique_ptr<Renderer> renderer;
	/// Exposure coefficient
	float exposure = 0.0;
	/// Ambient light coefficient
	float ambientColor = 0.0;
	/// MSAA samples per pixel
	int msaaSamples = 1;
	/// Maximum texture width/height
	int maxTexSize = -1;
	/// Render lines instead of faces
	bool wireframe = false;
	/// Render with bloom or not
	bool bloom = true;
	
	// Main planet collection
	/// Number of planets
	uint32_t planetCount = 0;
	/// Fixed planet parameters
	std::vector<Planet> planetParams;
	/// Dynamic planet state
	std::vector<PlanetState> planetStates;
	/// Index in the main collection of parent planet 
	std::vector<int> planetParents;

	/// Index in the main collection of planet the view follows
	size_t focusedPlanetId = 0; 
	/// Seconds since January 1st 1950 00:00
	double epoch = 0.0;
	/// Index in the timeWarpValues collection which indicates the current timewarp factor
	size_t timeWarpIndex = 0;
	/// Timewarp factors
	std::vector<double> timeWarpValues 
		= {1, 60, 60*10, 3600, 3600*3, 3600*12, 3600*24, 3600*24*10, 3600*24*365.2499};

	// VIEW CONTROL
	/// Mouse position of previous update cycle
	double preMousePosX = 0.0;
	/// Mouse position of previous update cycle
	double preMousePosY = 0.0;
	/// Indicates if we are currently dragging the view
	bool dragging = false;
	/// View speed (yaw, pitch, zoom)
	glm::vec3 viewSpeed = glm::vec3(0,0,0);
	/// Max view speed allowed
	float maxViewSpeed = 0.2;
	/// View speed damping for smooth effect
	float viewSmoothness = 0.85;

	// SWITCHING PLANETS
	/// Indicates if the view is switching from a planet to another
	bool isSwitching = false;
	/// Number of frames for a switch
	int switchFrames = 100; 
	/// Current frame of switching
	int switchFrameCurrent = 0;
	/// Zoom transition amount
	float switchPreviousDist = 0;
	/// Index in main collection of planet switching from
	int switchPreviousPlanet = -1; 

	/// Mouse sensitivity
	float sensitivity = 0.0004;

	// VIEW COORDINATES
	/// Polar coordinates (theta, phi, distance)
	glm::vec3 cameraPolar;
	/// Where the camera is looking at
	glm::dvec3 cameraCenter;
	/// Camera position in cartesian coordinates
	glm::dvec3 cameraPos;
	/// Vertical Field of view in radians
	float cameraFovy = glm::radians(40.f);

	/// GLFW Window pointer
	GLFWwindow *win = nullptr;
	/// Key currently held array
	std::bitset<512> keysHeld;
	/// Window width in pixels
	uint32_t width = 0;
	/// Window height in pixels
	uint32_t height = 0;
	/// Whether window is fullscreen or not
	bool fullscreen = false;
};