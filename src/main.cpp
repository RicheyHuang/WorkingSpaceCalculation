#include <iostream>
#include <cmath>

int computeFocalLength(double working_distance, double fov_width)
{
    double distance_film_to_lens = 17.5;
    double lens_length           = 4.8;
    double D = distance_film_to_lens + lens_length + working_distance;
    /// D = u + v

    double resolution_width = 1280;
    double resolution_height= 720;
    double pixel_width = 3.75e-3;
    double pixel_height= 3.75e-3;

    /// For 130M Cameras
    double chip_width = resolution_width * pixel_width;
    double chip_height= resolution_height* pixel_height;

    /// For 1200M Cameras
//    double chip_width = 13.075;
//    double chip_height = 8.827;


    double distance_between_cams = 50;

    double f = ( pow( D, 2 ) - pow( ( (fov_width + distance_between_cams - chip_width) * D ) / ( fov_width + distance_between_cams + chip_width ) , 2 ) ) / ( 4 * D );
    /// f: focal length, 1/f = 1/u + 1/v

    double v;
    /// v: image distance
    double u;
    /// u: object distance
    u = ( D + sqrt( D * D - 4 * D * f) ) / 2;
    v = ( D - sqrt( D * D - 4 * D * f) ) / 2;
    /// answer = ( -b + sqrt( b*b - 4ac ) )/2a or ( -b - sqrt( b*b - 4ac ) )/2a

    double theta_horizontal = 2 * atan( (chip_width/2)/v );;
    /// angle range of a single camera in horizontal direction

    double theta_vertical = 2 * atan( (chip_height/2)/v );;
    /// angle range of a single camera in vertical direction

    double d = (distance_between_cams/2) / tan(theta_horizontal/2);
    /// d: minimal working distance

    double fov_height= u * tan( theta_vertical / 2 ) * 2;

    double single_cam_fov_width = u * tan( theta_horizontal / 2 ) * 2;
    double single_cam_fov_height= fov_height;

    printf("Focal Length: %6.3f mm\n", f);
    printf("fov width for depth cam:  %6.3f mm\n", fov_width);
    printf("fov height for depth cam: %6.3f mm\n", fov_height);
    printf("fov width for single cam:  %6.3f mm\n", single_cam_fov_width);
    printf("fov height for single cam:  %6.3f mm\n", single_cam_fov_height);
    printf("Minimal Working Distance: %6.3f mm\n", d);

    return 0;
}

int computeFov(double f, double working_distance)
{
    double distance_film_to_lens = 17.5;
    double lens_length           = 4.8;
    double D = distance_film_to_lens + lens_length + working_distance;
    /// D = u + v
    double v;
    /// v: image distance
    double u;
    /// u: object distance

    u = ( D + sqrt( D * D - 4 * D * f) ) / 2;
    v = ( D - sqrt( D * D - 4 * D * f) ) / 2;
    /// f: focal length, 1/f = 1/u + 1/v
    /// answer = ( -b + sqrt( b*b - 4ac ) )/2a or ( -b - sqrt( b*b - 4ac ) )/2a

    double resolution_width = 1280;
    double resolution_height= 720;

    double pixel_width = 3.75e-3;
    double pixel_height= 3.75e-3;

    double chip_width = resolution_width * pixel_width;
    double chip_height= resolution_height* pixel_height;

    double theta_horizontal = 2 * atan( (chip_width/2)/v );
    /// angle range of a single camera in horizontal direction

    double theta_vertical = 2 * atan( (chip_height/2)/v );
    /// angle range of a single camera in vertical direction

    double distance_between_cams = 50;

    double d = (distance_between_cams/2) / tan(theta_horizontal/2);
    /// d: minimal working distance

    double fov_width = ( u - d ) * tan( theta_horizontal / 2 ) * 2;
    double fov_height= u * tan( theta_vertical / 2 ) * 2;

    double single_cam_fov_width = u * tan( theta_horizontal / 2 ) * 2;
    double single_cam_fov_height= fov_height;

    printf("fov width for depth cam:  %6.3f mm\n",   fov_width);
    printf("fov height for depth cam: %6.3f mm\n",   fov_height);
    printf("fov width for single cam:  %6.3f mm\n",  single_cam_fov_width);
    printf("fov height for single cam:  %6.3f mm\n", single_cam_fov_height);
    printf("Minimal Working Distance: %6.3f mm\n",   d);

    return 0;
}

double convertWorkingDistanceToRealObjectDistance(double working_distance)
{
    double distance_film_to_lens = 17.5;
    double lens_length           = 4.8;
    double D = distance_film_to_lens + lens_length + working_distance;
    /// D = u + v
    double u;
    /// u: object distance
    double f = 16;
    /// f: focal length, 1/f = 1/u + 1/v
    u = ( D + sqrt( D * D - 4 * D * f) ) / 2;
    /// answer = ( -b + sqrt( b*b - 4ac ) )/2a or ( -b - sqrt( b*b - 4ac ) )/2a
    return u;
}

int main()
{
//    double working_distance = 650;
//    double fov_width = 310;
//    computeFocalLength(working_distance, fov_width);

    double working_distance  = 750;
    double f = 12;
    computeFov(f, working_distance);

//    double u = convertWorkingDistanceToRealObjectDistance(350);
//    printf("u = %3.6f \n", u);

    return 0;
}