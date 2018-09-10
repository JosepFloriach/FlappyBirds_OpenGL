//
// Created by Josep on 13/08/2018.
//

#include "ShadersSource.h"

const std::string ShadersSource::DefaultVert =
        "precision mediump float;"
        "attribute vec3 vertexPosition;"
        "uniform mat4 MVP;"
        "void main()"
        "{"
        "   gl_Position =  MVP * vec4(vertexPosition,1);"
        "}";

const std::string ShadersSource::DefaultFrag =
        "precision mediump float;"
        "uniform float r;"
        "uniform float g;"
        "uniform float b;"
        "uniform float a;"
        "void main()"
        "{"
        "   gl_FragColor = vec4(r, g, b, 1.0);"
        "}";
