/*
 * Copyright (C) 1997-2001 Id Software, Inc.
 * Copyright (C) 2016-2017 Daniel Gibson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * OpenGL3 refresher: Handling shaders
 *
 * =======================================================================
 */

#include "header/local.h"

static GLuint
CompileShader(GLenum shaderType, const char* shaderSrc, const char* shaderSrc2)
{
	GLuint shader = glCreateShader(shaderType);

	const char* sources[2] = { shaderSrc, shaderSrc2 };
	int numSources = shaderSrc2 != NULL ? 2 : 1;
	GLint status;

	glShaderSource(shader, numSources, sources, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
	{
		char buf[2048];
		char* bufPtr = buf;
		int bufLen = sizeof(buf);
		GLint infoLogLength;
		const char* shaderTypeStr = "";

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		if(infoLogLength >= bufLen)
		{
			bufPtr = malloc(infoLogLength+1);
			bufLen = infoLogLength+1;
			if(bufPtr == NULL)
			{
				bufPtr = buf;
				bufLen = sizeof(buf);
				R_Printf(PRINT_ALL, "WARN: In CompileShader(), malloc(%d) failed!\n", infoLogLength+1);
			}
		}

		glGetShaderInfoLog(shader, bufLen, NULL, bufPtr);
		switch(shaderType)
		{
			case GL_VERTEX_SHADER:   shaderTypeStr = "Vertex"; break;
			case GL_FRAGMENT_SHADER: shaderTypeStr = "Fragment"; break;
			case GL_GEOMETRY_SHADER: shaderTypeStr = "Geometry"; break;
			/* not supported in OpenGL3.2 and we're unlikely to need/use them anyway
			case GL_COMPUTE_SHADER:  shaderTypeStr = "Compute"; break;
			case GL_TESS_CONTROL_SHADER:    shaderTypeStr = "TessControl"; break;
			case GL_TESS_EVALUATION_SHADER: shaderTypeStr = "TessEvaluation"; break;
			*/
		}
		R_Printf(PRINT_ALL, "ERROR: Compiling %s Shader failed: %s\n", shaderTypeStr, bufPtr);
		glDeleteShader(shader);

		if(bufPtr != buf)  free(bufPtr);

		return 0;
	}

	return shader;
}

static GLuint
CreateShaderProgram(int numShaders, const GLuint* shaders)
{
	int i=0;
	GLuint shaderProgram = glCreateProgram();
	GLint status;

	if(shaderProgram == 0)
	{
		R_Printf(PRINT_ALL, "ERROR: Couldn't create a new Shader Program!\n");
		return 0;
	}

	for(i=0; i<numShaders; ++i)
	{
		glAttachShader(shaderProgram, shaders[i]);
	}

	// make sure all shaders use the same attribute locations for common attributes
	// (so the same VAO can easily be used with different shaders)
	glBindAttribLocation(shaderProgram, GL3_ATTRIB_POSITION, "position");
	glBindAttribLocation(shaderProgram, GL3_ATTRIB_TEXCOORD, "texCoord");
	glBindAttribLocation(shaderProgram, GL3_ATTRIB_LMTEXCOORD, "lmTexCoord");
	glBindAttribLocation(shaderProgram, GL3_ATTRIB_COLOR, "vertColor");
	glBindAttribLocation(shaderProgram, GL3_ATTRIB_NORMAL, "normal");
	glBindAttribLocation(shaderProgram, GL3_ATTRIB_LIGHTFLAGS, "lightFlags");

	// the following line is not necessary/implicit (as there's only one output)
	// glBindFragDataLocation(shaderProgram, 0, "outColor"); XXX would this even be here?

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if(status != GL_TRUE)
	{
		char buf[2048];
		char* bufPtr = buf;
		int bufLen = sizeof(buf);
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		if(infoLogLength >= bufLen)
		{
			bufPtr = malloc(infoLogLength+1);
			bufLen = infoLogLength+1;
			if(bufPtr == NULL)
			{
				bufPtr = buf;
				bufLen = sizeof(buf);
				R_Printf(PRINT_ALL, "WARN: In CreateShaderProgram(), malloc(%d) failed!\n", infoLogLength+1);
			}
		}

		glGetProgramInfoLog(shaderProgram, bufLen, NULL, bufPtr);

		R_Printf(PRINT_ALL, "ERROR: Linking shader program failed: %s\n", bufPtr);

		glDeleteProgram(shaderProgram);

		if(bufPtr != buf)  free(bufPtr);

		return 0;
	}

	for(i=0; i<numShaders; ++i)
	{
		// after linking, they don't need to be attached anymore.
		// no idea  why they even are, if they don't have to..
		glDetachShader(shaderProgram, shaders[i]);
	}

	return shaderProgram;
}

#define MULTILINE_STRING( x )	x

// ############## shaders for 2D rendering (HUD, menus, console, videos, ..) #####################

static const char* vertexSrc2D = MULTILINE_STRING("#version 150\n\n"
"\n"
"\t\tin vec2 position; // GL3_ATTRIB_POSITION\n"
"\t\tin vec2 texCoord; // GL3_ATTRIB_TEXCOORD\n"
"\n"
"\t\t// for UBO shared between 2D shaders\n"
"\t\tlayout (std140) uniform uni2D\n"
"\t\t{\n"
"\t\t\tmat4 trans;\n"
"\t\t};\n"
"\n"
"\t\tout vec2 passTexCoord;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tgl_Position = trans * vec4(position, 0.0, 1.0);\n"
"\t\t\tpassTexCoord = texCoord;\n"
"\t\t}"
);

static const char* fragmentSrc2D = MULTILINE_STRING("#version 150\n\n"
"\n"
"\t\tin vec2 passTexCoord;\n"
"\n"
"\t\t// for UBO shared between all shaders (incl. 2D)\n"
"\t\tlayout (std140) uniform uniCommon\n"
"\t\t{\n"
"\t\t\tfloat gamma;\n"
"\t\t\tfloat intensity;\n"
"\t\t\tfloat intensity2D; // for HUD, menu etc\n"
"\n"
"\t\t\tvec4 color;\n"
"\t\t};\n"
"\n"
"\t\tuniform sampler2D tex;\n"
"\n"
"\t\tout vec4 outColor;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec4 texel = texture(tex, passTexCoord);\n"
"\t\t\t// the gl1 renderer used glAlphaFunc(GL_GREATER, 0.666);\n"
"\t\t\t// and glEnable(GL_ALPHA_TEST); for 2D rendering\n"
"\t\t\t// this should do the same\n"
"\t\t\tif(texel.a <= 0.666)\n"
"\t\t\t\tdiscard;\n"
"\n"
"\t\t\t// apply gamma correction and intensity\n"
"\t\t\ttexel.rgb *= intensity2D;\n"
"\t\t\toutColor.rgb = pow(texel.rgb, vec3(gamma));\n"
"\t\t\toutColor.a = texel.a; // I think alpha shouldn't be modified by gamma and intensity\n"
"\t\t}"
);

// 2D color only rendering, GL3_Draw_Fill(), GL3_Draw_FadeScreen()
static const char* vertexSrc2Dcolor = MULTILINE_STRING("#version 150\n\n"
"\n"
"\t\tin vec2 position; // GL3_ATTRIB_POSITION\n"
"\n"
"\t\t// for UBO shared between 2D shaders\n"
"\t\tlayout (std140) uniform uni2D\n"
"\t\t{\n"
"\t\t\tmat4 trans;\n"
"\t\t};\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tgl_Position = trans * vec4(position, 0.0, 1.0);\n"
"\t\t}"
);

static const char* fragmentSrc2Dcolor = MULTILINE_STRING("#version 150\n\n"
"\n"
"\t\t// for UBO shared between all shaders (incl. 2D)\n"
"\t\tlayout (std140) uniform uniCommon\n"
"\t\t{\n"
"\t\t\tfloat gamma;\n"
"\t\t\tfloat intensity;\n"
"\t\t\tfloat intensity2D; // for HUD, menus etc\n"
"\n"
"\t\t\tvec4 color;\n"
"\t\t};\n"
"\n"
"\t\tout vec4 outColor;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec3 col = color.rgb * intensity2D;\n"
"\t\t\toutColor.rgb = pow(col, vec3(gamma));\n"
"\t\t\toutColor.a = color.a;\n"
"\t\t}"
);

// ############## shaders for 3D rendering #####################

static const char* vertexCommon3D = MULTILINE_STRING("#version 150\n\n"
"\n"
"\t\tin vec3 position;   // GL3_ATTRIB_POSITION\n"
"\t\tin vec2 texCoord;   // GL3_ATTRIB_TEXCOORD\n"
"\t\tin vec2 lmTexCoord; // GL3_ATTRIB_LMTEXCOORD\n"
"\t\tin vec4 vertColor;  // GL3_ATTRIB_COLOR\n"
"\t\tin vec3 normal;     // GL3_ATTRIB_NORMAL\n"
"\t\tin uint lightFlags; // GL3_ATTRIB_LIGHTFLAGS\n"
"\n"
"\t\tout vec2 passTexCoord;\n"
"\n"
"\t\t// for UBO shared between all 3D shaders\n"
"\t\tlayout (std140) uniform uni3D\n"
"\t\t{\n"
"\t\t\tmat4 transProj;\n"
"\t\t\tmat4 transView;\n"
"\t\t\tmat4 transModel;\n"
"\n"
"\t\t\tfloat scroll; // for SURF_FLOWING\n"
"\t\t\tfloat time;\n"
"\t\t\tfloat alpha;\n"
"\t\t\tfloat overbrightbits;\n"
"\t\t\tfloat particleFadeFactor;\n"
"\t\t\tfloat _pad_1; // AMDs legacy windows driver needs this, otherwise uni3D has wrong size\n"
"\t\t\tfloat _pad_2;\n"
"\t\t\tfloat _pad_3;\n"
"\t\t};"
);

static const char* fragmentCommon3D = MULTILINE_STRING("#version 150\n\n"
"\n"
"\t\tin vec2 passTexCoord;\n"
"\n"
"\t\tout vec4 outColor;\n"
"\n"
"\t\t// for UBO shared between all shaders (incl. 2D)\n"
"\t\tlayout (std140) uniform uniCommon\n"
"\t\t{\n"
"\t\t\tfloat gamma; // this is 1.0/vid_gamma\n"
"\t\t\tfloat intensity;\n"
"\t\t\tfloat intensity2D; // for HUD, menus etc\n"
"\n"
"\t\t\tvec4 color; // really?\n"
"\n"
"\t\t};\n"
"\t\t// for UBO shared between all 3D shaders\n"
"\t\tlayout (std140) uniform uni3D\n"
"\t\t{\n"
"\t\t\tmat4 transProj;\n"
"\t\t\tmat4 transView;\n"
"\t\t\tmat4 transModel;\n"
"\n"
"\t\t\tfloat scroll; // for SURF_FLOWING\n"
"\t\t\tfloat time;\n"
"\t\t\tfloat alpha;\n"
"\t\t\tfloat overbrightbits;\n"
"\t\t\tfloat particleFadeFactor;\n"
"\t\t\tfloat _pad_1; // AMDs legacy windows driver needs this, otherwise uni3D has wrong size\n"
"\t\t\tfloat _pad_2;\n"
"\t\t\tfloat _pad_3;\n"
"\t\t};"
);

static const char* vertexSrc3D = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from vertexCommon3D\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tpassTexCoord = texCoord;\n"
"\t\t\tgl_Position = transProj * transView * transModel * vec4(position, 1.0);\n"
"\t\t}"
);

static const char* vertexSrc3Dflow = MULTILINE_STRING(
"\n"
"\t\t// it gets attributes and uniforms from vertexCommon3D\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tpassTexCoord = texCoord + vec2(scroll, 0);\n"
"\t\t\tgl_Position = transProj * transView * transModel * vec4(position, 1.0);\n"
"\t\t}"
);

static const char* vertexSrc3Dlm = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from vertexCommon3D\n"
"\n"
"\t\tout vec2 passLMcoord;\n"
"\t\tout vec3 passWorldCoord;\n"
"\t\tout vec3 passNormal;\n"
"\t\tflat out uint passLightFlags;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tpassTexCoord = texCoord;\n"
"\t\t\tpassLMcoord = lmTexCoord;\n"
"\t\t\tvec4 worldCoord = transModel * vec4(position, 1.0);\n"
"\t\t\tpassWorldCoord = worldCoord.xyz;\n"
"\t\t\tvec4 worldNormal = transModel * vec4(normal, 0.0f);\n"
"\t\t\tpassNormal = normalize(worldNormal.xyz);\n"
"\t\t\tpassLightFlags = lightFlags;\n"
"\n"
"\t\t\tgl_Position = transProj * transView * worldCoord;\n"
"\t\t}"
);

static const char* vertexSrc3DlmFlow = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from vertexCommon3D\n"
"\n"
"\t\tout vec2 passLMcoord;\n"
"\t\tout vec3 passWorldCoord;\n"
"\t\tout vec3 passNormal;\n"
"\t\tflat out uint passLightFlags;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tpassTexCoord = texCoord + vec2(scroll, 0);\n"
"\t\t\tpassLMcoord = lmTexCoord;\n"
"\t\t\tvec4 worldCoord = transModel * vec4(position, 1.0);\n"
"\t\t\tpassWorldCoord = worldCoord.xyz;\n"
"\t\t\tvec4 worldNormal = transModel * vec4(normal, 0.0f);\n"
"\t\t\tpassNormal = normalize(worldNormal.xyz);\n"
"\t\t\tpassLightFlags = lightFlags;\n"
"\n"
"\t\t\tgl_Position = transProj * transView * worldCoord;\n"
"\t\t}"
);

static const char* fragmentSrc3D = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tuniform sampler2D tex;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec4 texel = texture(tex, passTexCoord);\n"
"\n"
"\t\t\t// apply intensity and gamma\n"
"\t\t\ttexel.rgb *= intensity;\n"
"\t\t\toutColor.rgb = pow(texel.rgb, vec3(gamma));\n"
"\t\t\toutColor.a = texel.a*alpha; // I think alpha shouldn't be modified by gamma and intensity\n"
"\t\t}"
);

static const char* fragmentSrc3Dwater = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tuniform sampler2D tex;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec4 texel = texture(tex, passTexCoord);\n"
"\n"
"\t\t\t// apply intensity and gamma\n"
"\t\t\ttexel.rgb *= intensity*0.5;\n"
"\t\t\toutColor.rgb = pow(texel.rgb, vec3(gamma));\n"
"\t\t\toutColor.a = texel.a*alpha; // I think alpha shouldn't be modified by gamma and intensity\n"
"\t\t}"
);

static const char* fragmentSrc3Dlm = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tstruct DynLight { // gl3UniDynLight in C\n"
"\t\t\tvec3 lightOrigin;\n"
"\t\t\tfloat _pad;\n"
"\t\t\t//vec3 lightColor;\n"
"\t\t\t//float lightIntensity;\n"
"\t\t\tvec4 lightColor; // .a is intensity; this way it also works on OSX...\n"
"\t\t\t// (otherwise lightIntensity always contained 1 there)\n"
"\t\t};\n"
"\n"
"\t\tlayout (std140) uniform uniLights\n"
"\t\t{\n"
"\t\t\tDynLight dynLights[32];\n"
"\t\t\tuint numDynLights;\n"
"\t\t\tuint _pad1; uint _pad2; uint _pad3; // FFS, AMD!\n"
"\t\t};\n"
"\n"
"\t\tuniform sampler2D tex;\n"
"\n"
"\t\tuniform sampler2D lightmap0;\n"
"\t\tuniform sampler2D lightmap1;\n"
"\t\tuniform sampler2D lightmap2;\n"
"\t\tuniform sampler2D lightmap3;\n"
"\n"
"\t\tuniform vec4 lmScales[4];\n"
"\n"
"\t\tin vec2 passLMcoord;\n"
"\t\tin vec3 passWorldCoord;\n"
"\t\tin vec3 passNormal;\n"
"\t\tflat in uint passLightFlags;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec4 texel = texture(tex, passTexCoord);\n"
"\n"
"\t\t\t// apply intensity\n"
"\t\t\ttexel.rgb *= intensity;\n"
"\n"
"\t\t\t// apply lightmap\n"
"\t\t\tvec4 lmTex = texture(lightmap0, passLMcoord) * lmScales[0];\n"
"\t\t\tlmTex     += texture(lightmap1, passLMcoord) * lmScales[1];\n"
"\t\t\tlmTex     += texture(lightmap2, passLMcoord) * lmScales[2];\n"
"\t\t\tlmTex     += texture(lightmap3, passLMcoord) * lmScales[3];\n"
"\n"
"\t\t\tif(passLightFlags != 0u)\n"
"\t\t\t{\n"
"\t\t\t\t// TODO: or is hardcoding 32 better?\n"
"\t\t\t\tfor(uint i=0u; i<numDynLights; ++i)\n"
"\t\t\t\t{\n"
"\t\t\t\t\t// I made the following up, it's probably not too cool..\n"
"\t\t\t\t\t// it basically checks if the light is on the right side of the surface\n"
"\t\t\t\t\t// and, if it is, sets intensity according to distance between light and pixel on surface\n"
"\n"
"\t\t\t\t\t// dyn light number i does not affect this plane, just skip it\n"
"\t\t\t\t\tif((passLightFlags & (1u << i)) == 0u)  continue;\n"
"\n"
"\t\t\t\t\tfloat intens = dynLights[i].lightColor.a;\n"
"\n"
"\t\t\t\t\tvec3 lightToPos = dynLights[i].lightOrigin - passWorldCoord;\n"
"\t\t\t\t\tfloat distLightToPos = length(lightToPos);\n"
"\t\t\t\t\tfloat fact = max(0, intens - distLightToPos - 52);\n"
"\n"
"\t\t\t\t\t// move the light source a bit further above the surface\n"
"\t\t\t\t\t// => helps if the lightsource is so close to the surface (e.g. grenades, rockets)\n"
"\t\t\t\t\t//    that the dot product below would return 0\n"
"\t\t\t\t\t// (light sources that are below the surface are filtered out by lightFlags)\n"
"\t\t\t\t\tlightToPos += passNormal*32.0;\n"
"\n"
"\t\t\t\t\t// also factor in angle between light and point on surface\n"
"\t\t\t\t\tfact *= max(0, dot(passNormal, normalize(lightToPos)));\n"
"\n"
"\n"
"\t\t\t\t\tlmTex.rgb += dynLights[i].lightColor.rgb * fact * (1.0/256.0);\n"
"\t\t\t\t}\n"
"\t\t\t}\n"
"\n"
"\t\t\tlmTex.rgb *= overbrightbits;\n"
"\t\t\toutColor = lmTex*texel;\n"
"\t\t\toutColor.rgb = pow(outColor.rgb, vec3(gamma)); // apply gamma correction to result\n"
"\n"
"\t\t\toutColor.a = 1; // lightmaps aren't used with translucent surfaces\n"
"\t\t}"
);

static const char* fragmentSrc3Dcolor = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec4 texel = color;\n"
"\n"
"\t\t\t// apply gamma correction and intensity\n"
"\t\t\t// texel.rgb *= intensity; TODO: use intensity here? (this is used for beams)\n"
"\t\t\toutColor.rgb = pow(texel.rgb, vec3(gamma));\n"
"\t\t\toutColor.a = texel.a*alpha; // I think alpha shouldn't be modified by gamma and intensity\n"
"\t\t}"
);

static const char* fragmentSrc3Dsky = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tuniform sampler2D tex;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec4 texel = texture(tex, passTexCoord);\n"
"\n"
"\t\t\t// TODO: something about GL_BLEND vs GL_ALPHATEST etc\n"
"\n"
"\t\t\t// apply gamma correction\n"
"\t\t\t// texel.rgb *= intensity; // TODO: really no intensity for sky?\n"
"\t\t\toutColor.rgb = pow(texel.rgb, vec3(gamma));\n"
"\t\t\toutColor.a = texel.a*alpha; // I think alpha shouldn't be modified by gamma and intensity\n"
"\t\t}"
);

static const char* fragmentSrc3Dsprite = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tuniform sampler2D tex;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec4 texel = texture(tex, passTexCoord);\n"
"\n"
"\t\t\t// apply gamma correction and intensity\n"
"\t\t\ttexel.rgb *= intensity;\n"
"\t\t\toutColor.rgb = pow(texel.rgb, vec3(gamma));\n"
"\t\t\toutColor.a = texel.a*alpha; // I think alpha shouldn't be modified by gamma and intensity\n"
"\t\t}"
);

static const char* fragmentSrc3DspriteAlpha = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tuniform sampler2D tex;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec4 texel = texture(tex, passTexCoord);\n"
"\n"
"\t\t\tif(texel.a <= 0.666)\n"
"\t\t\t\tdiscard;\n"
"\n"
"\t\t\t// apply gamma correction and intensity\n"
"\t\t\ttexel.rgb *= intensity;\n"
"\t\t\toutColor.rgb = pow(texel.rgb, vec3(gamma));\n"
"\t\t\toutColor.a = texel.a*alpha; // I think alpha shouldn't be modified by gamma and intensity\n"
"\t\t}"
);

static const char* vertexSrc3Dwater = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from vertexCommon3D\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec2 tc = texCoord;\n"
"\t\t\ttc.s += sin( texCoord.t*0.125 + time ) * 4;\n"
"\t\t\ttc.s += scroll;\n"
"\t\t\ttc.t += sin( texCoord.s*0.125 + time ) * 4;\n"
"\t\t\ttc *= 1.0/64.0; // do this last\n"
"\t\t\tpassTexCoord = tc;\n"
"\n"
"\t\t\tgl_Position = transProj * transView * transModel * vec4(position, 1.0);\n"
"\t\t}"
);

static const char* vertexSrcAlias = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from vertexCommon3D\n"
"\n"
"\t\tout vec4 passColor;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tpassColor = vertColor*overbrightbits;\n"
"\t\t\tpassTexCoord = texCoord;\n"
"\t\t\tgl_Position = transProj * transView * transModel * vec4(position, 1.0);\n"
"\t\t}"
);

static const char* fragmentSrcAlias = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tuniform sampler2D tex;\n"
"\n"
"\t\tin vec4 passColor;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec4 texel = texture(tex, passTexCoord);\n"
"\n"
"\t\t\t// apply gamma correction and intensity\n"
"\t\t\ttexel.rgb *= intensity;\n"
"\t\t\ttexel.a *= alpha; // is alpha even used here?\n"
"\t\t\ttexel *= min(vec4(1.5), passColor);\n"
"\n"
"\t\t\toutColor.rgb = pow(texel.rgb, vec3(gamma));\n"
"\t\t\toutColor.a = texel.a; // I think alpha shouldn't be modified by gamma and intensity\n"
"\t\t}"
);

static const char* fragmentSrcAliasColor = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tin vec4 passColor;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec4 texel = passColor;\n"
"\n"
"\t\t\t// apply gamma correction and intensity\n"
"\t\t\t// texel.rgb *= intensity; // TODO: color-only rendering probably shouldn't use intensity?\n"
"\t\t\ttexel.a *= alpha; // is alpha even used here?\n"
"\t\t\toutColor.rgb = pow(texel.rgb, vec3(gamma));\n"
"\t\t\toutColor.a = texel.a; // I think alpha shouldn't be modified by gamma and intensity\n"
"\t\t}"
);

static const char* vertexSrcParticles = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from vertexCommon3D\n"
"\n"
"\t\tout vec4 passColor;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tpassColor = vertColor;\n"
"\t\t\tgl_Position = transProj * transView * transModel * vec4(position, 1.0);\n"
"\n"
"\t\t\t// abusing texCoord for pointSize, pointDist for particles\n"
"\t\t\tfloat pointDist = texCoord.y*0.1; // with factor 0.1 it looks good.\n"
"\n"
"\t\t\tgl_PointSize = texCoord.x/pointDist;\n"
"\t\t}"
);

static const char* fragmentSrcParticles = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tin vec4 passColor;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\tvec2 offsetFromCenter = 2.0*(gl_PointCoord - vec2(0.5, 0.5)); // normalize so offset is between 0 and 1 instead 0 and 0.5\n"
"\t\t\tfloat distSquared = dot(offsetFromCenter, offsetFromCenter);\n"
"\t\t\tif(distSquared > 1.0) // this makes sure the particle is round\n"
"\t\t\t\tdiscard;\n"
"\n"
"\t\t\tvec4 texel = passColor;\n"
"\n"
"\t\t\t// apply gamma correction and intensity\n"
"\t\t\t//texel.rgb *= intensity; TODO: intensity? Probably not?\n"
"\t\t\toutColor.rgb = pow(texel.rgb, vec3(gamma));\n"
"\n"
"\t\t\t// I want the particles to fade out towards the edge, the following seems to look nice\n"
"\t\t\ttexel.a *= min(1.0, particleFadeFactor*(1.0 - distSquared));\n"
"\n"
"\t\t\toutColor.a = texel.a; // I think alpha shouldn't be modified by gamma and intensity\n"
"\t\t}"
);

static const char* fragmentSrcParticlesSquare = MULTILINE_STRING("\n"
"\n"
"\t\t// it gets attributes and uniforms from fragmentCommon3D\n"
"\n"
"\t\tin vec4 passColor;\n"
"\n"
"\t\tvoid main()\n"
"\t\t{\n"
"\t\t\t// outColor = passColor;\n"
"\t\t\t// so far we didn't use gamma correction for square particles, but this way\n"
"\t\t\t// uniCommon is referenced so hopefully Intels Ivy Bridge HD4000 GPU driver\n"
"\t\t\t// for Windows stops shitting itself (see https://github.com/yquake2/yquake2/issues/391)\n"
"\t\t\toutColor.rgb = pow(passColor.rgb, vec3(gamma));\n"
"\t\t\toutColor.a = passColor.a;\n"
"\t\t}"
);


#undef MULTILINE_STRING

enum {
	GL3_BINDINGPOINT_UNICOMMON,
	GL3_BINDINGPOINT_UNI2D,
	GL3_BINDINGPOINT_UNI3D,
	GL3_BINDINGPOINT_UNILIGHTS
};

static qboolean
initShader2D(gl3ShaderInfo_t* shaderInfo, const char* vertSrc, const char* fragSrc)
{
	GLuint shaders2D[2] = {0};
	GLuint blockIndex;
	GLuint prog = 0;

	if(shaderInfo->shaderProgram != 0)
	{
		R_Printf(PRINT_ALL, "WARNING: calling initShader2D for gl3ShaderInfo_t that already has a shaderProgram!\n");
		glDeleteProgram(shaderInfo->shaderProgram);
	}

	//shaderInfo->uniColor = shaderInfo->uniProjMatrix = shaderInfo->uniModelViewMatrix = -1;
	shaderInfo->shaderProgram = 0;
	shaderInfo->uniLmScales = -1;

	shaders2D[0] = CompileShader(GL_VERTEX_SHADER, vertSrc, NULL);
	if(shaders2D[0] == 0)  return false;

	shaders2D[1] = CompileShader(GL_FRAGMENT_SHADER, fragSrc, NULL);
	if(shaders2D[1] == 0)
	{
		glDeleteShader(shaders2D[0]);
		return false;
	}

	prog = CreateShaderProgram(2, shaders2D);

	// I think the shaders aren't needed anymore once they're linked into the program
	glDeleteShader(shaders2D[0]);
	glDeleteShader(shaders2D[1]);

	if(prog == 0)
	{
		return false;
	}

	shaderInfo->shaderProgram = prog;
	GL3_UseProgram(prog);

	// Bind the buffer object to the uniform blocks
	blockIndex = glGetUniformBlockIndex(prog, "uniCommon");
	if(blockIndex != GL_INVALID_INDEX)
	{
		GLint blockSize;
		glGetActiveUniformBlockiv(prog, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		if(blockSize != sizeof(gl3state.uniCommonData))
		{
			R_Printf(PRINT_ALL, "WARNING: OpenGL driver disagrees with us about UBO size of 'uniCommon': %i vs %i\n",
					blockSize, (int)sizeof(gl3state.uniCommonData));

			goto err_cleanup;
		}

		glUniformBlockBinding(prog, blockIndex, GL3_BINDINGPOINT_UNICOMMON);
	}
	else
	{
		R_Printf(PRINT_ALL, "WARNING: Couldn't find uniform block index 'uniCommon'\n");
		// TODO: clean up?
		return false;
	}
	blockIndex = glGetUniformBlockIndex(prog, "uni2D");
	if(blockIndex != GL_INVALID_INDEX)
	{
		GLint blockSize;
		glGetActiveUniformBlockiv(prog, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		if(blockSize != sizeof(gl3state.uni2DData))
		{
			R_Printf(PRINT_ALL, "WARNING: OpenGL driver disagrees with us about UBO size of 'uni2D'\n");
			goto err_cleanup;
		}

		glUniformBlockBinding(prog, blockIndex, GL3_BINDINGPOINT_UNI2D);
	}
	else
	{
		R_Printf(PRINT_ALL, "WARNING: Couldn't find uniform block index 'uni2D'\n");
		goto err_cleanup;
	}

	return true;

err_cleanup:
	if(shaders2D[0] != 0)  glDeleteShader(shaders2D[0]);
	if(shaders2D[1] != 0)  glDeleteShader(shaders2D[1]);

	if(prog != 0)  glDeleteProgram(prog);

	return false;
}

static qboolean
initShader3D(gl3ShaderInfo_t* shaderInfo, const char* vertSrc, const char* fragSrc)
{
	GLuint shaders3D[2] = {0};
	char lmName[10] = "lightmapX";
	GLint lmScalesLoc;
	GLuint prog = 0;
	GLuint blockIndex;
	GLint texLoc;
	int i=0;

	if(shaderInfo->shaderProgram != 0)
	{
		R_Printf(PRINT_ALL, "WARNING: calling initShader3D for gl3ShaderInfo_t that already has a shaderProgram!\n");
		glDeleteProgram(shaderInfo->shaderProgram);
	}

	shaderInfo->shaderProgram = 0;
	shaderInfo->uniLmScales = -1;

	shaders3D[0] = CompileShader(GL_VERTEX_SHADER, vertexCommon3D, vertSrc);
	if(shaders3D[0] == 0)  return false;

	shaders3D[1] = CompileShader(GL_FRAGMENT_SHADER, fragmentCommon3D, fragSrc);
	if(shaders3D[1] == 0)
	{
		glDeleteShader(shaders3D[0]);
		return false;
	}

	prog = CreateShaderProgram(2, shaders3D);

	if(prog == 0)
	{
		goto err_cleanup;
	}

	GL3_UseProgram(prog);

	// Bind the buffer object to the uniform blocks
	blockIndex = glGetUniformBlockIndex(prog, "uniCommon");
	if(blockIndex != GL_INVALID_INDEX)
	{
		GLint blockSize;
		glGetActiveUniformBlockiv(prog, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		if(blockSize != sizeof(gl3state.uniCommonData))
		{
			R_Printf(PRINT_ALL, "WARNING: OpenGL driver disagrees with us about UBO size of 'uniCommon'\n");

			goto err_cleanup;
		}

		glUniformBlockBinding(prog, blockIndex, GL3_BINDINGPOINT_UNICOMMON);
	}
	else
	{
		R_Printf(PRINT_ALL, "WARNING: Couldn't find uniform block index 'uniCommon'\n");

		goto err_cleanup;
	}
	blockIndex = glGetUniformBlockIndex(prog, "uni3D");
	if(blockIndex != GL_INVALID_INDEX)
	{
		GLint blockSize;
		glGetActiveUniformBlockiv(prog, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		if(blockSize != sizeof(gl3state.uni3DData))
		{
			R_Printf(PRINT_ALL, "WARNING: OpenGL driver disagrees with us about UBO size of 'uni3D'\n");
			R_Printf(PRINT_ALL, "         driver says %d, we expect %d\n", blockSize, (int)sizeof(gl3state.uni3DData));

			goto err_cleanup;
		}

		glUniformBlockBinding(prog, blockIndex, GL3_BINDINGPOINT_UNI3D);
	}
	else
	{
		R_Printf(PRINT_ALL, "WARNING: Couldn't find uniform block index 'uni3D'\n");

		goto err_cleanup;
	}
	blockIndex = glGetUniformBlockIndex(prog, "uniLights");
	if(blockIndex != GL_INVALID_INDEX)
	{
		GLint blockSize;
		glGetActiveUniformBlockiv(prog, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		if(blockSize != sizeof(gl3state.uniLightsData))
		{
			R_Printf(PRINT_ALL, "WARNING: OpenGL driver disagrees with us about UBO size of 'uniLights'\n");
			R_Printf(PRINT_ALL, "         OpenGL says %d, we say %d\n", blockSize, (int)sizeof(gl3state.uniLightsData));

			goto err_cleanup;
		}

		glUniformBlockBinding(prog, blockIndex, GL3_BINDINGPOINT_UNILIGHTS);
	}
	// else: as uniLights is only used in the LM shaders, it's ok if it's missing

	// make sure texture is GL_TEXTURE0
	texLoc = glGetUniformLocation(prog, "tex");
	if(texLoc != -1)
	{
		glUniform1i(texLoc, 0);
	}

	// ..  and the 4 lightmap texture use GL_TEXTURE1..4
	for(i=0; i<4; ++i)
	{
		GLint lmLoc;
		lmName[8] = '0' + i;
		lmLoc = glGetUniformLocation(prog, lmName);
		if(lmLoc != -1)
		{
			glUniform1i(lmLoc, i+1); // lightmap0 belongs to GL_TEXTURE1, lightmap1 to GL_TEXTURE2 etc
		}
	}

	lmScalesLoc = glGetUniformLocation(prog, "lmScales");
	shaderInfo->uniLmScales = lmScalesLoc;
	if(lmScalesLoc != -1)
	{
		shaderInfo->lmScales[0] = HMM_Vec4(1.0f, 1.0f, 1.0f, 1.0f);

		for(i=1; i<4; ++i)  shaderInfo->lmScales[i] = HMM_Vec4(0.0f, 0.0f, 0.0f, 0.0f);

		glUniform4fv(lmScalesLoc, 4, shaderInfo->lmScales[0].Elements);
	}

	shaderInfo->shaderProgram = prog;

	// I think the shaders aren't needed anymore once they're linked into the program
	glDeleteShader(shaders3D[0]);
	glDeleteShader(shaders3D[1]);

	return true;

err_cleanup:

	if(shaders3D[0] != 0)  glDeleteShader(shaders3D[0]);
	if(shaders3D[1] != 0)  glDeleteShader(shaders3D[1]);

	if(prog != 0)  glDeleteProgram(prog);

	return false;
}

static void initUBOs(void)
{
	gl3state.uniCommonData.gamma = 1.0f/vid_gamma->value;
	gl3state.uniCommonData.intensity = gl3_intensity->value;
	gl3state.uniCommonData.intensity2D = gl3_intensity_2D->value;
	gl3state.uniCommonData.color = HMM_Vec4(1, 1, 1, 1);

	glGenBuffers(1, &gl3state.uniCommonUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, gl3state.uniCommonUBO);
	glBindBufferBase(GL_UNIFORM_BUFFER, GL3_BINDINGPOINT_UNICOMMON, gl3state.uniCommonUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(gl3state.uniCommonData), &gl3state.uniCommonData, GL_DYNAMIC_DRAW);

	// the matrix will be set to something more useful later, before being used
	gl3state.uni2DData.transMat4 = HMM_Mat4();

	glGenBuffers(1, &gl3state.uni2DUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, gl3state.uni2DUBO);
	glBindBufferBase(GL_UNIFORM_BUFFER, GL3_BINDINGPOINT_UNI2D, gl3state.uni2DUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(gl3state.uni2DData), &gl3state.uni2DData, GL_DYNAMIC_DRAW);

	// the matrices will be set to something more useful later, before being used
	gl3state.uni3DData.transProjMat4 = HMM_Mat4();
	gl3state.uni3DData.transViewMat4 = HMM_Mat4();
	gl3state.uni3DData.transModelMat4 = gl3_identityMat4;
	gl3state.uni3DData.scroll = 0.0f;
	gl3state.uni3DData.time = 0.0f;
	gl3state.uni3DData.alpha = 1.0f;
	// gl3_overbrightbits 0 means "no scaling" which is equivalent to multiplying with 1
	gl3state.uni3DData.overbrightbits = (gl3_overbrightbits->value <= 0.0f) ? 1.0f : gl3_overbrightbits->value;
	gl3state.uni3DData.particleFadeFactor = gl3_particle_fade_factor->value;

	glGenBuffers(1, &gl3state.uni3DUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, gl3state.uni3DUBO);
	glBindBufferBase(GL_UNIFORM_BUFFER, GL3_BINDINGPOINT_UNI3D, gl3state.uni3DUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(gl3state.uni3DData), &gl3state.uni3DData, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &gl3state.uniLightsUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, gl3state.uniLightsUBO);
	glBindBufferBase(GL_UNIFORM_BUFFER, GL3_BINDINGPOINT_UNILIGHTS, gl3state.uniLightsUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(gl3state.uniLightsData), &gl3state.uniLightsData, GL_DYNAMIC_DRAW);

	gl3state.currentUBO = gl3state.uniLightsUBO;
}

static qboolean createShaders(void)
{
	const char* particleFrag;

	if(!initShader2D(&gl3state.si2D, vertexSrc2D, fragmentSrc2D))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for textured 2D rendering!\n");
		return false;
	}
	if(!initShader2D(&gl3state.si2Dcolor, vertexSrc2Dcolor, fragmentSrc2Dcolor))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for color-only 2D rendering!\n");
		return false;
	}
	if(!initShader3D(&gl3state.si3Dlm, vertexSrc3Dlm, fragmentSrc3Dlm))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for textured 3D rendering with lightmap!\n");
		return false;
	}
	if(!initShader3D(&gl3state.si3Dtrans, vertexSrc3D, fragmentSrc3D))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for rendering translucent 3D things!\n");
		return false;
	}
	if(!initShader3D(&gl3state.si3DcolorOnly, vertexSrc3D, fragmentSrc3Dcolor))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for flat-colored 3D rendering!\n");
		return false;
	}
	/*
	if(!initShader3D(&gl3state.si3Dlm, vertexSrc3Dlm, fragmentSrc3D))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for blending 3D lightmaps rendering!\n");
		return false;
	}
	*/
	if(!initShader3D(&gl3state.si3Dturb, vertexSrc3Dwater, fragmentSrc3Dwater))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for water rendering!\n");
		return false;
	}
	if(!initShader3D(&gl3state.si3DlmFlow, vertexSrc3DlmFlow, fragmentSrc3Dlm))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for scrolling textured 3D rendering with lightmap!\n");
		return false;
	}
	if(!initShader3D(&gl3state.si3DtransFlow, vertexSrc3Dflow, fragmentSrc3D))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for scrolling textured translucent 3D rendering!\n");
		return false;
	}
	if(!initShader3D(&gl3state.si3Dsky, vertexSrc3D, fragmentSrc3Dsky))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for sky rendering!\n");
		return false;
	}
	if(!initShader3D(&gl3state.si3Dsprite, vertexSrc3D, fragmentSrc3Dsprite))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for sprite rendering!\n");
		return false;
	}
	if(!initShader3D(&gl3state.si3DspriteAlpha, vertexSrc3D, fragmentSrc3DspriteAlpha))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for alpha-tested sprite rendering!\n");
		return false;
	}
	if(!initShader3D(&gl3state.si3Dalias, vertexSrcAlias, fragmentSrcAlias))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for rendering textured models!\n");
		return false;
	}
	if(!initShader3D(&gl3state.si3DaliasColor, vertexSrcAlias, fragmentSrcAliasColor))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for rendering flat-colored models!\n");
		return false;
	}

	particleFrag = fragmentSrcParticles;
	if(gl3_particle_square->value != 0.0f)
	{
		particleFrag = fragmentSrcParticlesSquare;
	}

	if(!initShader3D(&gl3state.siParticle, vertexSrcParticles, particleFrag))
	{
		R_Printf(PRINT_ALL, "WARNING: Failed to create shader program for rendering particles!\n");
		return false;
	}

	gl3state.currentShaderProgram = 0;

	return true;
}

qboolean GL3_InitShaders(void)
{
	initUBOs();

	return createShaders();
}

static void deleteShaders(void)
{
	const gl3ShaderInfo_t siZero = {0};
	gl3ShaderInfo_t* si;

	for(si = &gl3state.si2D; si <= &gl3state.siParticle; ++si)
	{
		if(si->shaderProgram != 0)  glDeleteProgram(si->shaderProgram);
		*si = siZero;
	}
}

void GL3_ShutdownShaders(void)
{
	deleteShaders();

	// let's (ab)use the fact that all 4 UBO handles are consecutive fields
	// of the gl3state struct
	glDeleteBuffers(4, &gl3state.uniCommonUBO);
	gl3state.uniCommonUBO = gl3state.uni2DUBO = gl3state.uni3DUBO = gl3state.uniLightsUBO = 0;
}

qboolean GL3_RecreateShaders(void)
{
	// delete and recreate the existing shaders (but not the UBOs)
	deleteShaders();
	return createShaders();
}

static _inline void
updateUBO(GLuint ubo, GLsizeiptr size, void* data)
{
	if(gl3state.currentUBO != ubo)
	{
		gl3state.currentUBO = ubo;
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	}

	// http://docs.gl/gl3/glBufferSubData says  "When replacing the entire data store,
	// consider using glBufferSubData rather than completely recreating the data store
	// with glBufferData. This avoids the cost of reallocating the data store."
	// no idea why glBufferData() doesn't just do that when size doesn't change, but whatever..
	// however, it also says glBufferSubData() might cause a stall so I DON'T KNOW!
	// on Linux/nvidia, by just looking at the fps, glBufferData() and glBufferSubData() make no difference
	// TODO: STREAM instead DYNAMIC?

#if 1
	// this seems to be reasonably fast everywhere.. glMapBuffer() seems to be a bit faster on OSX though..
	glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
#elif 0
	// on OSX this is super slow (200fps instead of 470-500), BUT it is as fast as glBufferData() when orphaning first
	// nvidia/linux-blob doesn't care about this vs glBufferData()
	// AMD open source linux (R3 370) is also slower here (not as bad as OSX though)
	// intel linux doesn't seem to care either (maybe 3% faster, but that might be imagination)
	// AMD Windows legacy driver (Radeon HD 6950) doesn't care, all 3 alternatives seem to be equally fast
	//glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW); // orphan
	glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
#else
	// with my current nvidia-driver (GTX 770, 375.39), the following *really* makes it slower. (<140fps instead of ~850)
	// on OSX (Intel Haswell Iris Pro, OSX 10.11) this is fastest (~500fps instead of ~470)
	// on Linux/intel (Ivy Bridge HD-4000, Linux 4.4) this might be a tiny bit faster than the alternatives..
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW); // orphan
	GLvoid* ptr = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
	memcpy(ptr, data, size);
	glUnmapBuffer(GL_UNIFORM_BUFFER);
#endif

	// TODO: another alternative: glMapBufferRange() and each time update a different part
	//       of buffer asynchronously (GL_MAP_UNSYNCHRONIZED_BIT) => ringbuffer style
	//       when starting again from the beginning, synchronization must happen I guess..
	//       also, orphaning might be necessary
	//       and somehow make sure the new range is used by the UBO => glBindBufferRange()
	//  see http://git.quintin.ninja/mjones/Dolphin/blob/4a463f4588e2968c499236458c5712a489622633/Source/Plugins/Plugin_VideoOGL/Src/ProgramShaderCache.cpp#L207
	//   or https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoBackends/OGL/ProgramShaderCache.cpp
}

void GL3_UpdateUBOCommon(void)
{
	updateUBO(gl3state.uniCommonUBO, sizeof(gl3state.uniCommonData), &gl3state.uniCommonData);
}

void GL3_UpdateUBO2D(void)
{
	updateUBO(gl3state.uni2DUBO, sizeof(gl3state.uni2DData), &gl3state.uni2DData);
}

void GL3_UpdateUBO3D(void)
{
	updateUBO(gl3state.uni3DUBO, sizeof(gl3state.uni3DData), &gl3state.uni3DData);
}

void GL3_UpdateUBOLights(void)
{
	updateUBO(gl3state.uniLightsUBO, sizeof(gl3state.uniLightsData), &gl3state.uniLightsData);
}
