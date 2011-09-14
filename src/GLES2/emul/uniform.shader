struct LightSourceParameters
{
	vec4 ambient;               // Aclarri
	vec4 diffuse;               // Dcli
	vec4 specular;              // Scli
	vec4 position;              // Ppli
	vec4 halfVector;            // Derived: Hi
	vec3 spotDirection;         // Sdli
	float spotExponent;         // Srli
	float spotCutoff;           // Crli
	                            // (range: [0.0,90.0], 180.0)
/*
	float spotCosCutoff;        // Derived: cos(Crli)
	                            // (range: [1.0,0.0],-1.0)
*/
	float constantAttenuation;  // K0
	float linearAttenuation;    // K1
	float quadraticAttenuation; // K2
};

struct MaterialParameters
{
	vec4 emission;    // Ecm
	vec4 ambient;     // Acm
	vec4 diffuse;     // Dcm
	vec4 specular;    // Scm
	float shininess;  // Srm
};

uniform vec4 u_ambient;

#define MAX_LIGHTS 8

uniform LightSourceParameters u_LightSource[MAX_LIGHTS];
uniform MaterialParameters    u_FrontMaterial;
uniform MaterialParameters    u_BackMaterial;

struct LightProducts
{
	vec4 ambient; // Acm * Acli
	vec4 diffuse; // Dcm * Dcli
	vec4 specular; // Scm * Scli
};

uniform mat4 u_ModelViewProjectionMatrix; // A constant representing the combined model/view/projection matrix.
uniform mat4 u_ModelViewMatrix;
uniform mat4 u_NormalMatrix;  // A constant representing the combined model/view matrix.
uniform int u_lightMap;

uniform int u_AlphaTestFunc;
uniform float u_AlphaTestValue;
