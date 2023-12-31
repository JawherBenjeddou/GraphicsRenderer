#pragma once
#include<iostream>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "Shader.h"
#include "DebugUtils.h"

class Renderer {

public:

	//DELETE COPY CONSTRUCTOR
	Renderer(const Renderer&) = delete;

	//DELETE MOVE CONSTRUCTOR
	Renderer(const Renderer&&) = delete;

	//DELETE COPY ASSIGN OPERATOR
	Renderer& operator=(const Renderer&) = delete;

	//DELETE MOVE ASSIGN OPERATOR
	Renderer& operator=(const Renderer&&) = delete;



	



private:
	Renderer() = default;

};