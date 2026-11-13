/*
Cámara: ojo (0, 2.2, 6), mira a (0, 0.8, 0), arriba (0, 1, 0), fov vertical 45 [°].
Fondo: uniforme (0.05, 0.07, 0.1).
Piso: plano por (0, 0, 0), normal (0, 1, 0). Checker: size=0.4, kd=(0.85, 0.85, 0.85), ka=(0.05,
0.05, 0.05), kd2=(0.06, 0.3, 0.1), ka2=(0.004, 0.018, 0.006).
Esferas: centro (x, 0.9, 0). Dielectric: ks=(1, 1, 1), shininess=150, transparency=0.9, salvo lo
indicado.
• Maciza: x=-2, radio 0.8, ior=1.5.
• Hueca, superficie exterior: x=0, radio 0.8, ior=1.5.
• Hueca, superficie interior: x=0, radio 0.768, ior=1/1.5, ks=(0, 0, 0).
• Burbuja: x=2, radio 0.8, ior=1/1.33.
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

void build_scene_06(Scene& scene, Camera& camera)
{

    // camara
    camera.look_at(glm::vec3(0.0f, 2.2f, 6.0f),   // ojo
               glm::vec3(0.0f, 0.8f, 0.0f),   // hacia dónde mira
               glm::vec3(0.0f, 1.0f, 0.0f),   // arriba
               45.0f);                        // fov vertical


    //fondo
    scene.set_background(glm::vec3(0.05f, 0.07f, 0.1f));


    // Piso: 
    auto floor = std::make_shared<Checker>();
    floor->size = 0.4f;
    floor->kd   = glm::vec3(0.85f);  
    floor->ka   = glm::vec3(0.05f);
    floor->kd2  = glm::vec3(0.06f, 0.3f, 0.1f);    
    floor->ka2  = glm::vec3(0.004f, 0.018f, 0.006f);
    floor->ks   = glm::vec3(0.0f);


    //esfera maciza
    auto maciza = std::make_shared<Dielectric>();
    maciza->ks = glm::vec3(1.0f);
    maciza->shininess = 150.0f;
    maciza->ior = 1.5f;
    maciza->transparency = 0.9f;

    //esfera hueca, superficie exterior
    auto hueca_ext = std::make_shared<Dielectric>();
    hueca_ext->ks = glm::vec3(1.0f);
    hueca_ext->shininess = 150.0f;
    hueca_ext->ior = 1.5f;
    hueca_ext->transparency = 0.9f;

    //esfera hueca, superficie interior
    auto hueca_int = std::make_shared<Dielectric>();
    hueca_int->ks = glm::vec3(0.0f);
    hueca_int->shininess = 150.0f;
    hueca_int->ior = 1/1.5f;
    hueca_int->transparency = 0.9f;

    //esfera burbuja
    auto burbuja = std::make_shared<Dielectric>();
    burbuja->ks = glm::vec3(1.0f);
    burbuja->shininess = 150.0f;
    burbuja->ior = 1/1.33f;
    burbuja->transparency = 0.9f;


    //piso
    scene.add_object(std::make_shared<Plane>(glm::vec3(0.0f),            // punto por el que pasa
                                            glm::vec3(0.0f, 1.0f, 0.0f), // normal
                                            floor));                     // material


    //esfera maciza
    scene.add_object(std::make_shared<Sphere>(glm::vec3(-2.0f, 0.9f, 0.0f),// centro
                                            0.8f, // radio
                                            maciza));

    //esfera hueca, superficie exterior
    scene.add_object(std::make_shared<Sphere>(glm::vec3(0.0f, 0.9f, 0.0f),// centro
                                            0.8f, // radio
                                            hueca_ext));

    //esfera hueca, superficie interior
    scene.add_object(std::make_shared<Sphere>(glm::vec3(0.0f, 0.9f, 0.0f),// centro
                                            0.768f, // radio
                                            hueca_int));

    //esfera burbuja
    scene.add_object(std::make_shared<Sphere>(glm::vec3(2.0f, 0.9f, 0.0f),// centro
                                            0.8f, // radio
                                            burbuja));


                                            
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