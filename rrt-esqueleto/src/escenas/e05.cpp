/*
Cámara: ojo (0, 1.8, 5), mira a (0, 0.7, 0), arriba (0, 1, 0), fov vertical 45 [°].
Fondo: uniforme (0.05, 0.07, 0.1).
Piso: plano por (0, 0, 0), normal (0, 1, 0). Checker: size=0.4, kd=(0.85, 0.85, 0.85), ka=(0.05,
0.05, 0.05), kd2=(0.08, 0.08, 0.3), ka2=(0.005, 0.005, 0.018).
Esferas: centro (x, 0.8, 0), radio 0.7. Dielectric: ks=(1, 1, 1), shininess=150, transparency=0.9.
• Aire: x=-2.4, ior=1.
• Agua: x=-0.8, ior=1.33.
• Vidrio: x=0.8, ior=1.5.
• Diamante: x=2.4, ior=2.42.
Luz 1: posición (-3, 6, 4), color (2.6, 2.6, 2.6).
Luz 2: posición (4, 4, 3), color (1, 1, 1).
*/

#include <memory>
#include <escenas.h>
#include <plane.h>
#include <sphere.h>
#include <checker.h>
#include <mirror.h>
#include <triangle.h>
#include <dielectric.h>

void build_scene_05(Scene& scene, Camera& camera)
{

    // camara
    camera.look_at(glm::vec3(0.0f, 1.8f, 5.0f),   // ojo
               glm::vec3(0.0f, 0.7f, 0.0f),   // hacia dónde mira
               glm::vec3(0.0f, 1.0f, 0.0f),   // arriba
               45.0f);                        // fov vertical


    //fondo
    scene.set_background(glm::vec3(0.05f, 0.07f, 0.1f));


    // Piso: 
    auto floor = std::make_shared<Checker>();
    floor->size = 0.4f;
    floor->kd   = glm::vec3(0.85f);  
    floor->ka   = glm::vec3(0.05f);
    floor->kd2  = glm::vec3(0.08f, 0.08f, 0.3f);    
    floor->ka2  = glm::vec3(0.005f, 0.005f, 0.018f);
    floor->ks   = glm::vec3(0.0f);


    //esfera de aire
    auto air = std::make_shared<Dielectric>();
    air->ks = glm::vec3(1.0f);
    air->shininess = 150.0f;
    air->ior = 1.0f;
    air->transparency = 0.9f;

    //esfera de agua
    auto water = std::make_shared<Dielectric>();
    water->ks = glm::vec3(1.0f);
    water->shininess = 150.0f;
    water->ior = 1.33f;
    water->transparency = 0.9f;

    //esfera de vidrio
    auto glass = std::make_shared<Dielectric>();
    glass->ks = glm::vec3(1.0f);
    glass->shininess = 150.0f;
    glass->ior = 1.5f;
    glass->transparency = 0.9f;

    //esfera de diamante
    auto diamond = std::make_shared<Dielectric>();
    diamond->ks = glm::vec3(1.0f);
    diamond->shininess = 150.0f;
    diamond->ior = 2.42f;
    diamond->transparency = 0.9f;


    //piso
    scene.add_object(std::make_shared<Plane>(glm::vec3(0.0f),            // punto por el que pasa
                                            glm::vec3(0.0f, 1.0f, 0.0f), // normal
                                            floor));                     // material


    //esfera de aire
    scene.add_object(std::make_shared<Sphere>(glm::vec3(-2.4f, 0.8f, 0.0f),// centro
                                            0.7f, // radio
                                            air));

    //esfera de agua
    scene.add_object(std::make_shared<Sphere>(glm::vec3(-0.8f, 0.8f, 0.0f),// centro
                                            0.7f, // radio
                                            water));

    //esfera de vidrio
    scene.add_object(std::make_shared<Sphere>(glm::vec3(0.8f, 0.8f, 0.0f),// centro
                                            0.7f, // radio
                                            glass));

    //esfera de diamante
    scene.add_object(std::make_shared<Sphere>(glm::vec3(2.4f, 0.8f, 0.0f),// centro
                                            0.7f, // radio
                                            diamond));



    const glm::vec3 att(1.0f, 0.12f, 0.02f);
    //Luz 1
    scene.add_light(Light(glm::vec3(-3.0f, 6.0f, 4.0f),   // posición
                      glm::vec3(2.6f),    // color
                      att));

    //Luz 2
    scene.add_light(Light(glm::vec3(4.0f, 4.0f, 3.0f),   // posición
                      glm::vec3(1.0f),    // color
                      att));


    scene.set_max_depth(8U);
}