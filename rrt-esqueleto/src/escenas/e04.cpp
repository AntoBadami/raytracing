/*
Cámara: ojo (0, 2.4, 9), mira a (0, 1, 0), arriba (0, 1, 0), fov vertical 40 [°].
Fondo: degradado según la componente y de la dirección normalizada del rayo, de (0.55, 0.65, 0.8) en
el horizonte a (0.05, 0.12, 0.35) en el cenit (set_background con dos colores). Hacia abajo se mantiene
el color del horizonte.
Piso: plano por (0, 0, 0), normal (0, 1, 0). Checker: size=1, kd=(0.75, 0.75, 0.75), ka=(0.12,
0.12, 0.12), kd2=(0.05, 0.15, 0.45), ka2=(0.01, 0.03, 0.08).
Esfera de vidrio (maciza): centro (-1.3, 1.2, 2.5), radio 1.2. Dielectric: ior=1.5,
transparency=0.8, ks=(1, 1, 1), shininess=100.
Esfera de agua (maciza): centro (1.7, 0.8, 3), radio 0.8. Dielectric: ior=1.33, transparency=0.9,
ks=(1, 1, 1), shininess=100.
Esferas opacas: radio 0.8. Diffuse con ka = 0.1 * kd, ks=(0.4, 0.4, 0.4), shininess=50.
• Roja: centro (-2.6, 0.8, -1.5), kd=(0.75, 0.1, 0.08).
• Amarilla: centro (-0.5, 0.8, -2), kd=(0.85, 0.6, 0.05).
• Verde: centro (1.8, 0.8, -1), kd=(0.1, 0.55, 0.2).
Luz 1: posición (-5, 9, 7), color (3, 3, 3).
Luz 2: posición (6, 7, 5), color (2, 2, 2).
*/

#include <memory>
#include <escenas.h>
#include <plane.h>
#include <sphere.h>
#include <checker.h>
#include <mirror.h>
#include <triangle.h>
#include <dielectric.h>

void build_scene_04(Scene& scene, Camera& camera)
{

    // camara
    camera.look_at(glm::vec3(0.0f, 2.4f, 9.0f),   // ojo
               glm::vec3(0.0f, 1.0f, 0.0f),   // hacia dónde mira
               glm::vec3(0.0f, 1.0f, 0.0f),   // arriba
               40.0f);                        // fov vertical

    //fondo
    scene.set_background(glm::vec3(0.55f, 0.65f, 0.8f),
                         glm::vec3(0.05f, 0.12f, 0.35f));


    
    // Piso: 
    auto floor = std::make_shared<Checker>();
    floor->size = 1.0f;
    floor->kd   = glm::vec3(0.75f);  
    floor->ka   = glm::vec3(0.12f);
    floor->kd2  = glm::vec3(0.05f, 0.15f, 0.45f);    
    floor->ka2  = glm::vec3(0.01f, 0.03f, 0.08f);
    floor->ks   = glm::vec3(0.0f);


    //esfera de vidrio
    auto glass = std::make_shared<Dielectric>();
    glass->ks = glm::vec3(1.0f);
    glass->shininess = 100.0f;
    glass->ior = 1.5f;
    glass->transparency = 0.8f;

    
    //esfera de agua
    auto water = std::make_shared<Dielectric>();
    water->ks = glm::vec3(1.0f);
    water->shininess = 100.0f;
    water->ior = 1.33f;
    water->transparency = 0.9f;


    // Esfera roja
    auto ballred = std::make_shared<Diffuse>();
    ballred->ka = glm::vec3(0.1f) * glm::vec3(0.75f, 0.1f, 0.08f);
    ballred->kd = glm::vec3(0.75f, 0.1f, 0.08f);
    ballred->ks = glm::vec3(0.4f);
    ballred->shininess = 50.0f;

    // Esfera amarilla
    auto ballyellow = std::make_shared<Diffuse>();
    ballyellow->ka = glm::vec3(0.1f) * glm::vec3(0.85f, 0.6f, 0.05f);
    ballyellow->kd = glm::vec3(0.85f, 0.6f, 0.05f);
    ballyellow->ks = glm::vec3(0.4f);
    ballyellow->shininess = 50.0f;

    //esfera verde
    auto ballgreen = std::make_shared<Diffuse>();
    ballgreen->ka = glm::vec3(0.1f) * glm::vec3(0.1f, 0.55f, 0.2f);
    ballgreen->kd = glm::vec3(0.1f, 0.55f, 0.2f);
    ballgreen->ks = glm::vec3(0.4f);
    ballgreen->shininess = 50.0f;


    //piso
    scene.add_object(std::make_shared<Plane>(glm::vec3(0.0f),            // punto por el que pasa
                                            glm::vec3(0.0f, 1.0f, 0.0f), // normal
                                            floor));                     // material


    //esfera de vidrio
    scene.add_object(std::make_shared<Sphere>(glm::vec3(-1.3f, 1.2f, 2.5f),// centro
                                            1.2f, // radio
                                            glass));

    
    //esfera de agua
    scene.add_object(std::make_shared<Sphere>(glm::vec3(1.7f, 0.8f, 3.0f),// centro
                                            0.8f, // radio
                                            water));


    //esfera roja
    scene.add_object(std::make_shared<Sphere>(glm::vec3(-2.6f, 0.8f, -1.5f),// centro
                                            0.8f, // radio
                                            ballred));
    
    //esfera amarilla
    scene.add_object(std::make_shared<Sphere>(glm::vec3(-0.5f, 0.8f, -2.0f),// centro
                                            0.8f, // radio
                                            ballyellow));

    //esfera verde
    scene.add_object(std::make_shared<Sphere>(glm::vec3(1.8f, 0.8f, -1.0f),// centro
                                            0.8f, // radio
                                            ballgreen));
    

    const glm::vec3 att(1.0f, 0.12f, 0.02f);
    //Luz 1
    scene.add_light(Light(glm::vec3(-5.0f, 9.0f, 7.0f),   // posición
                      glm::vec3(3.0f),    // color
                      att));

    //Luz 2
    scene.add_light(Light(glm::vec3(6.0f, 7.0f, 5.0f),   // posición
                      glm::vec3(2.0f),    // color
                      att));


    scene.set_max_depth(8U);
}