/* Holds all module partitions for building the game engine. Naming scheme is:
*  framework:[namespace].[class]
*  Cyclic includes force each "namespace" to be in the same module file, refactoring
*  would fix this, but this was intended to match original design.
* 
*  If cyclic dependencies could be solved, ideally each "namespace" would be a single
*  module.
*/
export module framework;

// Core partitions
export import :core.application;
export import :core.camera2d;
export import :core.entity;
export import :core.window;

// Listener partitions
export import :listeners.keyboard;
export import :listeners.mouse;

// Manager partitions
export import :managers.asset;
export import :managers.entity;
export import :managers.state;

// Renderer partitions
export import :renderer.batch;
export import :renderer.shader;
export import :renderer.sprite;
export import :renderer.spritesheet;
export import :renderer.texture2d;

// State Partitions
export import :states.base;
export import :states.credits;
export import :states.game;
export import :states.intro;
export import :states.mainmenu;