#include "sphere.h"


Sphere::Sphere(std::vector<std::unique_ptr<Transform>> transformations, std::unique_ptr<Material>material, double radius, math::vec3<double> position)
            :Surface(std::move(transformations), std::move(material)), radius{radius}, position{position}{};


void Sphere::print(){
    std::cout<<"jestem w sferze" << radius << std::endl;
}

std::optional<std::shared_ptr<Intersection>> Sphere::checkIntersection(Ray *ray, double t_min, double t_max){
    
    // An Abstraction for Hittable Objects  https://raytracing.github.io/books/RayTracingInOneWeekend.html
    //You might note that the vector from center C=(Cx,Cy,Cz) to point P=(x,y,z)is (P−C), and therefore
    //(P(t)−C)⋅(P(t)−C)=r2 P(t) ray formula ; C - center of the sphere
    // (A+tb−C)⋅(A+tb−C)=r2 // A = origin of ray + t - times b normalized destination vector
    // t2b⋅b+2tb⋅(A−C)+(A−C)⋅(A−C)−r2=0

    math::vec3<double> eye{}; 
    eye = ray->getOrigin() - position; // origin of ray - center of sphere oc of ray
    auto a = ray->getDirection().SqrLenght();
    auto b = 2.0 * eye.dotProduct(ray->getDirection());
    auto c = eye.SqrLenght() - (radius*radius);
    auto delta = b*b - 4*a*c;
    if (delta >= 0){
        // choose closer root
        // create intersection and choose closer root
        // intersection.push_back(std::make_shared<Intersection>());
        delta = sqrt(delta);
        // right there we are creating the root and filling intersection data
        //
        double root = ((-b  - delta )/(2*a));
        //
        if (root < t_min || t_max < root){
            root = ((-b  + delta )/(2*a));
            if (root < t_min || t_max < root)
                return {};
        }
        auto rayPosition = ray->getMovedPoint(root);
        math::vec3<double> normal = ((rayPosition - position)/ radius);
        std::shared_ptr<Intersection> intersection = std::make_shared<Intersection>(rayPosition,normal, root);
        // direction of normal
        intersection->setFront(ray, normal);

        // filling the interection class
        // root cords
        // intersection->setRoot(root);
        // final position of ray
        // intersection->setPoint(rayPosition);
        // normals
        // intersection->setNormal((rayPosition - position)/ radius);

        //material
        auto m_point = getMaterial();
        //phong 
        intersection->setMaterialCoefficients(m_point->getKa(), m_point->getKd(), m_point->getKs(), m_point ->getExponent());
        intersection->setReflectanceTransmitanceRefraction(m_point->getReflectance(), m_point->getTransmitance(), m_point->getRefration());

        // CHECK WHICH TYPE OF MATERIAL !!!
        auto solid = dynamic_cast<materialSolid*>(m_point);
        if (solid!= nullptr){
            intersection->setColors(solid->getColor());
        }

        auto texture = dynamic_cast<materialTextured*> (m_point);
        if (texture != nullptr){
            intersection->setName(texture->getName());
        }
        return intersection;
    }
    return {};
};

