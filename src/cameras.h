/*
 * cameras.h
 *
 *  Created on: Feb 26, 2019
 *      Author: mahsa
 */

#ifndef CAMERAS_H_
#define CAMERAS_H_

#include "mainheader.h"
void *CameraBackUp(void *);
void *CameraFront(void *);
void *CameraBackDown(void *);
void *CameraLeft(void *);
void *CameraRight(void *);
void *Camera(void *);
bool ChckObstacle();

#endif /* CAMERAS_H_ */
