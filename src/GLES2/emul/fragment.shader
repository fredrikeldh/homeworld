#include "uniform.shader"

/*
varying vec3 vN;
varying vec3 v; 
#define MAX_LIGHTS 3 
void main (void) 
{ 

   // write Total Color: 
   gl_FragColor = gl_FrontLightModelProduct.sceneColor + finalColor; 
}
*/

uniform sampler2D u_tex0;

varying vec2 v_texCoord;
varying vec4 v_color;

#define GL_NEVER    
#define GL_LESS     
#define GL_EQUAL    
#define GL_LEQUAL   
#define GL_GREATER  
#define GL_NOTEQUAL 
#define GL_GEQUAL   
#define GL_ALWAYS   

void main()
{
	//calculate the fragment color based on the texture and the vertex color
	vec4 basecolor = texture2D( u_tex0, v_texCoord )* v_color;
	
	// Validate alpha value first
	alphafunc(basecolor);
	
	vec3 N = normalize(vN);
	
	for( int i = 0; i != MAX_LIGHTS; i++ )
	{
		if( !u_LightSource[i].enabled )
			break;
			
		vec4 frontLightProductAmbient   = u_FrontMaterial.ambient * u_LightSource[i].ambient;
		vec4 frontLightProductDiffuse   = u_FrontMaterial.diffuse * u_LightSource[i].diffuse;
		vec 4 frontLightProductSpecular = u_FrontMaterial.specular * u_LightSource[i].specular;
		//LightProducts backLightProduct  = u_BackMaterial * u_LightSource[i];
			
		vec3 L = normalize(u_LightSource[i].position.xyz - v); 
		vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0) 
		vec3 R = normalize(-reflect(L, N)); 

		//calculate Ambient Term: 
		vec4 Iamb = frontLightProductAmbient; 
		
		//calculate Diffuse Term: 
		vec4 Idiff =
			frontLightProductDiffuse
			* max(dot(N, L), 0.0);
		Idiff = clamp(Idiff, 0.0, 1.0); 

		// calculate Specular Term:
		vec4 Ispec =
			frontLightProductSpecular 
			* pow(max(dot(R, E),0.0), 0.3 * u_FrontMaterial.shininess);
		Ispec = clamp(Ispec, 0.0, 1.0); 
		
		basecolor += Iamb + Idiff + Ispec;
	}

	gl_FragColor = basecolor;
}

void alphafunc(vec4 basecolor)
{
	//if testing is enabled, check the alpha component and discard if zero
	if( u_AlphaTestFunc == GL_ALWAYS )
		return;
	
	if( basecolor.a == 0.0 || u_AlphaTestFunc == GL_NEVER )
		alphafunc_never(u_AlphaTestValue, basecolor.a);
	else if( u_AlphaTestFunc == GL_LESS )
		alphafunc_less(u_AlphaTestValue, basecolor.a);
	else if( u_AlphaTestFunc == GL_EQUAL )
		alphafunc_equal(u_AlphaTestValue, basecolor.a);
	else if( u_AlphaTestFunc == GL_LEQUAL )
		alphafunc_lequal(u_AlphaTestValue, basecolor.a);
	else if( u_AlphaTestFunc == GL_GREATER )
		alphafunc_greater(u_AlphaTestValue, basecolor.a);
	else if( u_AlphaTestFunc == GL_NOTEQUAL )
		alphafunc_notequal(u_AlphaTestValue, basecolor.a);
	else if( u_AlphaTestFunc == GL_GEQUAL )
		alphafunc_gequal(u_AlphaTestValue, basecolor.a);
}

void doDiscard(bool value)
{
	if( !value )
		discard;
}

void alphafunc_never(float test, float value)
{
	doDiscard(false);
}

void alphafunc_less(float test, float value)
{
	doDiscard(test > value);
}

void alphafunc_equal(float test, float value)
{
	doDiscard(test == value);
}

void alphafunc_lequal(float test, float value)
{
	doDiscard(test >= value);
}

void alphafunc_greater(float test, float value)
{
	doDiscard(test < value);
}

void alphafunc_notequal(float test, float value)
{
	doDiscard(test != value);
}

void alphafunc_gequal(float test, float value)
{
	doDiscard(test <= value);
}

