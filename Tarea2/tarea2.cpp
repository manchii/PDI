/*
 * Copyright (C) 2009-2015 by Pablo Alvarado
 *
 * This file is part of the course MP-6123 Digital Image Processing,
 * at the Costa Rica Institute of Technology.
 *
 * The LTI-Lib-2 is free software; you can redistribute it and/or
 * modify it under the terms of the BSD License.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the authors nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file   tarea02.cpp
 *         Homework for first contact with the LTI-Lib-2
 * \author Pablo Alvarado
 * \date   26.05.2012
 * revisions ..: $Id: pwc.cpp,v 1.2 2009/06/05 12:59:33 alvarado Exp $
 */

// Standard Headers: from ANSI C and GNU C Library
#include <cstdlib>  // Standard Library for C++
#include <getopt.h> // Functions to parse the command line arguments

// Standard Headers: STL
#include <iostream>
#include <string>
#include <fstream>

// LTI-Lib Headers
#include <ltiObject.h>
#include <ltiMath.h>     // General lti:: math and <cmath> functionality
#include <ltiTimer.h>    // To measure time

#include <ltiV4l2.h>
#include <ltiIOImage.h> // To read/write images from files (jpg, png, and bmp)
#include <ltiViewer2D.h>

#include <ltiLispStreamHandler.h>

// Ensure that the STL streaming is used.
using std::cout;
using std::cerr;
using std::endl;


/*
 * Help
 */
void usage()  {


  cout <<
    "usage: tarea02 [options] [<file>]\n\n" \
    "       -h|--help        show this help\n"\
    "       <file>           input image" << std::endl;
}

/*
 * Parse the line command arguments
 *
 * Set the filename with the given parameter, or an empty string otherwise
 */
void parse(int argc, char*argv[],std::string& filename) {

  int c;

  // We use the standard getopt.h functions here to parse the arguments.
  // Check the documentation of getopt.h for more information on this

  // structure for the long options.
  static struct option lopts[] = {
    {"help",no_argument,0,'h'},
    {0,0,0,0}
  };

  int optionIdx;

  while ((c = getopt_long(argc, argv, "h", lopts,&optionIdx)) != -1) {
    switch (c) {
    case 'h':
      usage();
      exit(EXIT_SUCCESS);
    default:
      cerr << "Option '-" << static_cast<char>(c) << "' not recognized."
           << endl;
    }
  }

  // Now try to read the image name
  if (optind < argc) {           // if there are still some arguments left...
    filename = argv[optind];  // with the given image file
  } else {
    filename = "";
  }
}

/*
 * Main method
 */
int main(int argc, char* argv[]) {

  // check if the user gave some filename
  std::string filename;
  parse(argc,argv,filename);

  if (!filename.empty()) {
    // the user just wants to show an image:

    // we need an object to load images
    lti::ioImage loader;

    // we also need an image object
    lti::image img;

    // load the image
    if (loader.load(filename,img)) {
      // image successfully loaded

      // we need a viewer
      static lti::viewer2D view;

      // and get its parameters
      lti::viewer2D::parameters vpar(view.getParameters());
      vpar.title = filename; // set the image name at the window's title bar
      view.setParameters(vpar);

      view.show(img); // show the image

      // wait for the user to close the window or to indicate
      bool theEnd = false;
      lti::viewer2D::interaction action;
      lti::ipoint pos;

      do {
        view.waitInteraction(action,pos); // wait for something to happen
        if (action == lti::viewer2D::Closed) { // window closed?
          theEnd = true; // we are ready here!
        }
      } while(!theEnd);


      return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;

  } else {

    // -----------------------------------
    // -----------------------------------
    //        PUT YOUR CODE HERE!!!
    // -----------------------------------
    // -----------------------------------

    static const char* confFile = "v4l2.lsp";

    lti::v4l2::parameters param;

    // try to read the configuration file
    std::ifstream in(confFile);
    bool write=true;
    if (in) {
      lti::lispStreamHandler lsh;
      lsh.use(in);
      write=!param.read(lsh);
    }
    if (write) {
      // something went wrong reading, write a new configuration file
      std::ofstream out(confFile);
      lti::lispStreamHandler lsh;
      lsh.use(out);
      param.write(lsh);
    }
    param.whiteBalanceTemperature=6500;
    param.backlightCompensation=100;
    // create the detector with the user specified configuration
    lti::v4l2 cam(param);

    // image handler
    lti::image img;

    // viewer2D init
    lti::viewer2D::parameters vPar;
//    vPar.mappingType = lti::viewer2DPainter::Optimal;
    static lti::viewer2D orig(vPar);

    // Interaction
  lti::viewer2D::interaction action;
  lti::ipoint pos;


    // loop flags
    bool ok,update;
    update=false;
    // Assigning camera to img
    if (!cam.apply(img)) {
      cout << "Error: " << cam.getStatusString() << endl;
      exit(EXIT_FAILURE);
    }

    float saturation = 0.5;
    float exposure=0;
    float brightness=1;
    // do while ok
    do{
      ok = cam.apply(img);
      orig.show(img);

      orig.getLastAction(action,pos);
      if (action.action == lti::viewer2D::KeyPressed || action.action == lti::viewer2D::ButtonPressed)  {
        switch(action.key) {
        case 'x':
        case 'X':
          std::cout << "/* message */" << '\n';
          ok = false;
          break;
        case lti::viewer2D::RightKey:
        case '+':
          exposure = lti::min(1.0f,exposure+0.10f);
          update=true;
          break;
        case lti::viewer2D::LeftKey:
        case '-':
          exposure = lti::max(0.0f,exposure-0.10f);
          update=true;
          break;
        case lti::viewer2D::UpKey:
          brightness = lti::min(1.0f,brightness+0.05f);
          update=true;
          break;
        case lti::viewer2D::DownKey:
          brightness = lti::max(0.0f,brightness-0.05f);
          update=true;
          break;
          case lti::viewer2D::WheelUp:
          saturation = lti::min(1.0f,saturation+0.01f);
          update=true;
          break;
          case lti::viewer2D::WheelDown:
          saturation = lti::max(0.0f,saturation-0.01f);
          update=true;
          break;
        default:
          cout << "<" << action.key << ">" << std::endl;
        }
      }
      if (update) {
        // Update parameters
        cout << " exposure: " << exposure << " brightness: " << brightness << " saturation: " << saturation<<endl;
        cam.setSaturation(lti::FeatureManual,saturation);
        cam.setBrightness(lti::FeatureManual, brightness);
        cam.setExposure(lti::FeatureManual,exposure);
        update=false;
      }

    }while(ok);
    std::ofstream out(confFile);
    lti::lispStreamHandler lsh;
    lsh.use(out);
    cam.dumpParameters(param);
    param.write(lsh);

//    cout << "Not done yet!  Try giving a image name" << endl;
//    usage();

    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}
