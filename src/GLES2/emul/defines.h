
//
// Add everything that's not already defined by GLES emulation
//

#define GL_FRONT           0x0404
#define GL_BACK            0x0405
#define GL_FRONT_AND_BACK  0x0408

#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504

// Applies subsequent matrix operations to the modelview matrix stack.
#define GL_MODELVIEW  0x1700
// Applies subsequent matrix operations to the projection matrix stack.
#define GL_PROJECTION 0x1701
/* Already defined in OpenGL ES 2.0
// Applies subsequent matrix operations to the texture matrix stack.
#define GL_TEXTURE    2
*/

#define GL_CURRENT_COLOR                  0x0B00
#define GL_CURRENT_TEXTURE_COORDS         0x0B03

#define GL_POINT_SMOOTH 0x0B10
#define GL_POINT_SIZE   0x0B11
#define GL_LINE_SMOOTH  0x0B20
#define GL_LIGHTING     0x0B50

#define GL_LIGHT_MODEL_LOCAL_VIEWER       0x0B51

// LightModelParameter
#define GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#define GL_LIGHT_MODEL_AMBIENT            0x0B53 
#define GL_SHADE_MODEL                    0x0B54

#define GL_FOG                            0x0B60
#define GL_FOG_INDEX                      0x0B61
// FogParameter
#define GL_FOG_DENSITY                    0x0B62
#define GL_FOG_START                      0x0B63
#define GL_FOG_END                        0x0B64
#define GL_FOG_MODE                       0x0B65
#define GL_FOG_COLOR                      0x0B66

#define GL_MATRIX_MODE       0x0BA0
#define GL_NORMALIZE         0x0BA1
#define GL_MODELVIEW_MATRIX  0x0BA6
#define GL_PROJECTION_MATRIX 0x0BA7

#define GL_ALPHA_TEST                     0x0BC0
#define GL_ALPHA_TEST_FUNC                0x0BC1
#define GL_ALPHA_TEST_REF                 0x0BC2
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1

#define GL_PERSPECTIVE_CORRECTION_HINT    0x0C50

#define GL_ALPHA_SCALE                    0x0D1C
#define GL_MAX_LIGHTS                     0x0D31

#define GL_MAX_CLIP_PLANES 0x0D32

// LightParameter
#define GL_AMBIENT  0x1200
#define GL_DIFFUSE  0x1201
#define GL_SPECULAR 0x1202
#define GL_POSITION 0x1203

#define GL_SPOT_DIRECTION                 0x1204
#define GL_SPOT_EXPONENT                  0x1205
#define GL_SPOT_CUTOFF                    0x1206
#define GL_CONSTANT_ATTENUATION           0x1207
#define GL_LINEAR_ATTENUATION             0x1208
#define GL_QUADRATIC_ATTENUATION          0x1209

#define GL_DOUBLE   0x140A

// MaterialParameter
#define GL_EMISSION            0x1600
#define GL_SHININESS           0x1601
#define GL_AMBIENT_AND_DIFFUSE 0x1602

#define GL_COLOR                          0x1800
#define GL_COLOR_INDEX                    0x1900

// ShadingModels
#define GL_FLAT   0x1D00
#define GL_SMOOTH 0x1D01

#define GL_TEXTURE_ENV_MODE               0x2200
#define GL_TEXTURE_ENV                    0x2300

#define GL_LIGHT0                         0x4000
#define GL_LIGHT1                         0x4001
#define GL_LIGHT2                         0x4002
#define GL_LIGHT3                         0x4003
#define GL_LIGHT4                         0x4004
#define GL_LIGHT5                         0x4005
#define GL_LIGHT6                         0x4006
#define GL_LIGHT7                         0x4007

// FogMode
#define GL_EXP                            0x0800
#define GL_EXP2                           0x0801

#define GL_RESCALE_NORMAL 0x803A

#define GL_RGB8                           0x8051

#define GL_VERTEX_ARRAY                   0x8074
#define GL_NORMAL_ARRAY                   0x8075
#define GL_COLOR_ARRAY                    0x8076
#define GL_INDEX_ARRAY                    0x8077
#define GL_TEXTURE_COORD_ARRAY            0x8078
#define GL_EDGE_FLAG_ARRAY                0x8079

#define GL_LIGHT_MODEL_COLOR_CONTROL      0x81F8
#define GL_SINGLE_COLOR                   0x81F9
#define GL_SEPARATE_SPECULAR_COLOR        0x81FA

#define GL_FOG_COORDINATE                 0x8451
#define GL_FRAGMENT_DEPTH                 0x8452
#define GL_FOG_COORD_ARRAY                0x8457
#define GL_SECONDARY_COLOR_ARRAY          0x845E

#define GL_FOG_COORD_SRC                  0x8450
#define GL_TEXTURE_FILTER_CONTROL         0x8500
#define GL_TEXTURE_LOD_BIAS               0x8501
#define GL_COMBINE_RGB                    0x8571
#define GL_COMBINE_ALPHA                  0x8572
#define GL_RGB_SCALE                      0x8573
#define GL_SRC0_RGB                       0x8580
#define GL_SRC1_RGB                       0x8581
#define GL_SRC2_RGB                       0x8582
#define GL_SRC0_ALPHA                     0x8588
#define GL_SRC1_ALPHA                     0x8589
#define GL_SRC2_ALPHA                     0x858A
#define GL_OPERAND0_RGB                   0x8590
#define GL_OPERAND1_RGB                   0x8591
#define GL_OPERAND2_RGB                   0x8592
#define GL_OPERAND0_ALPHA                 0x8598
#define GL_OPERAND1_ALPHA                 0x8599
#define GL_OPERAND2_ALPHA                 0x859A 
#define GL_POINT_SPRITE                   0x8861
#define GL_COORD_REPLACE                  0x8862

// TextureEnvMode
#define GL_MODULATE 0x2100
#define GL_DECAL    0x2101
#define GL_ADD      0x0104

// ClipPlaneName
#define GL_CLIP_PLANE0                    0x3000
#define GL_CLIP_PLANE1                    0x3001
#define GL_CLIP_PLANE2                    0x3002
#define GL_CLIP_PLANE3                    0x3003
#define GL_CLIP_PLANE4                    0x3004
#define GL_CLIP_PLANE5                    0x3005

// CullFaceMode

// LightName
#define GL_LIGHT0                         0x4000
#define GL_LIGHT1                         0x4001



