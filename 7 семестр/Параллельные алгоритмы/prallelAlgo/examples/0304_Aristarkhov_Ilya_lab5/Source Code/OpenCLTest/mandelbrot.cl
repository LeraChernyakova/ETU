uint3 get_color(uint steps) {
    steps = steps % 16;
    switch (steps) {
        case 0: return (uint3)(66, 30, 15);
        case 1: return (uint3)(25, 7, 26);
        case 2: return (uint3)(9, 1, 47);
        case 3: return (uint3)(4, 4, 73);
        case 4: return (uint3)(0, 7, 100);
        case 5: return (uint3)(12, 44, 138);
        case 6: return (uint3)(24, 82, 177);
        case 7: return (uint3)(57, 125, 209);
        case 8: return (uint3)(134, 181, 229);
        case 9: return (uint3)(211, 236, 248);
        case 10: return(uint3)(241, 233, 191);
        case 11: return(uint3)(248, 201, 95);
        case 12: return(uint3)(255, 170, 0);
        case 13: return(uint3)(204, 128, 0);
        case 14: return(uint3)(153, 87, 0);
        case 15: return(uint3)(106, 52, 3);
    }

    return (uint3)(0, 0, 0);
}


__kernel void mandelbrot(__write_only image2d_t out) {

    // Getting position of current work-item
    int2 pos = (int2)(get_global_id(0), get_global_id(1));

    // Getting total image size
    int2 size = get_image_dim(out);

    // Scaling x to range [-2.5; 1]
    float x0 = (float)pos.x / size.x;
    x0 = x0*3.25 - 2;

    // Scaling y to range [-1; 1]
    float y0 = (float)pos.y / size.y;
    y0 = y0*2.0 - 1.0;


    float x = 0.0;
    float y = 0.0;

    uint max_its = 256;
    uint i = 0;
    float d = 0.0;

    // Performing iterations until we run out of iterations or until d is grater than 4
    while (i < max_its && d < 4.0){
        float xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;

        d = x*x + y*y;
        i++;
    }

    uint4 color = (255, 255, 255, 255);

    // If d is less than 4 then we outside the mandelbrot figure. Otherwise take some color based on last iteration
    if (d < 4.0){
        color.xyz = (uint3)(0, 0, 0);
    } else {
        color.xyz = get_color(i);
    }

    // Writing result pixel
    write_imageui(out, pos, color);
}
