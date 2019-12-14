//
// Created by walter on 2017/2/12.
//

#ifndef FUNCTION_HPP
#define FUNCTION_HPP

/*
static void* car_in_handler(void* cp_in);

static void* car_out_handler(void* carpack_out);

static void* monitor(void* carpark_in);

static void initialise(CarPack *cp, int size);
*/

void* car_in_handler(void* cp_in);

void* car_out_handler(void* carpack_out);

void* monitor(void* carpark_in);

void initialise(CarPack *cp, int size);


#endif //FUNCTION_HPP
