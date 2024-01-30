#include <iostream>
#include <arv.h>
#include <opencv4/opencv2/opencv.hpp>

#include <stdlib.h>
#include <signal.h>

#include <stdio.h>

using namespace std;

int main(int argc, char **argv)
{
    ArvCamera *camera;
    ArvBuffer *buffer;
    GError *error = NULL;

    /* Connect to the first available camera */
    camera = arv_camera_new(NULL, &error);
    arv_camera_set_acquisition_mode(camera,ARV_ACQUISITION_MODE_CONTINUOUS, &error);
    if(ARV_IS_CAMERA(camera))
    {
        printf("Model name: '%s'\n", arv_camera_get_model_name(camera, NULL));
        printf("Serial number: '%s'\n", arv_camera_get_device_serial_number(camera, NULL));

        /* Acquire a single buffer */
        while(buffer = arv_camera_acquisition(camera, 1000000, &error)){
        buffer = arv_camera_acquisition(camera, 1000000, &error);

        if (ARV_IS_BUFFER(buffer))
        {

            /* Display some informations about the retrieved buffer */
            int width = arv_buffer_get_image_width(buffer);
            int height = arv_buffer_get_image_height(buffer);
            printf("Acquired %d×%d buffer\n", width, height);

            int bit_depth = ARV_PIXEL_FORMAT_BIT_PER_PIXEL(arv_buffer_get_image_pixel_format(buffer));
            printf("bit_depth: %d\n", bit_depth);

            int arv_row_stride = width * bit_depth / 8;
            printf("RowStride: %d\n", arv_row_stride);

            size_t buffer_size;
            void *framebuffer = (void *)arv_buffer_get_data(buffer, &buffer_size);
            printf("buffer_size: %ld\n", buffer_size);

            cv::Mat image(height, width, CV_8UC3, (unsigned char *)framebuffer);

            cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

            // Save the image to a file
            cv::imshow("final_image.jpg", image);
            cv::waitKey(1);
            /* Destroy the buffer */
            g_clear_object(&buffer);
        }


        }
        /* Destroy the camera instance */
        g_clear_object(&camera);
    }

    if (error != NULL)
    {
        /* An error happened, display the correspdonding message */
        printf("Error: %s\n", error->message);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

