/*
 * Copyright (C) 2007 by Pablo Alvarado
 *
 * This file is part of the LTI-Computer Vision Library 2 (LTI-Lib-2)
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
 * \file   surfLocalDescriptor.cpp
 *         Contains an example of use for the class lti::surfLocalDescriptor
 * \author Pablo Alvarado
 * \date   04.11.2007
 * revisions ..: $Id: matrixTransform.cpp,v 1.5 2011-08-29 14:17:33 alvarado Exp $
 */

// LTI-Lib Headers
#include "ltiObject.h"
#include "ltiIOImage.h"
#include "ltiMath.h"
#include "ltiPassiveWait.h"

#include "ltiPassiveWait.h"

#include "ltiMaximumFilter.h"
#include "ltiChannel8.h"

#include "ltiLispStreamHandler.h"

#include "ltiViewer2D.h" // The normal viewer
typedef lti::viewer2D viewer_type;




#include "dokladal.hpp"

/*
 * Help
 */
void usage() {
  cout << "Usage: matrixTransform [image] [-h]" << endl;
  cout << "Try some image transformations on the given image\n";
  cout << "  -h show this help." << endl;
}

/*
 * Parse the line command arguments
 */
void parseArgs(int argc, char*argv[],
               std::string& filename) {

  filename.clear();
  // check each argument of the command line
  for (int i=1; i<argc; i++) {
    if (*argv[i] == '-') {
      switch (argv[i][1]) {
        case 'h':
          usage();
          exit(EXIT_SUCCESS);
          break;
        default:
          break;
      }
    } else {
      filename = argv[i]; // guess that this is the filename
    }
  }
}

/*
 * Main method
 */
int main(int argc, char* argv[]) {
  static const char* confFile = "project.dat";

  std::string imgFile;
  parseArgs(argc,argv,imgFile);

  lti::ioImage loader; // used to load an image file

  lti::image imgRgba;
  lti::channel8 img;
  if (!loader.load(imgFile,imgRgba)) {
    std::cerr << "Could not read " << imgFile << ": "
              << loader.getStatusString()
              << std::endl;
    usage();
    exit(EXIT_FAILURE);
  }

  // Convert to grayscale
  img.castFrom(imgRgba);

  std::ifstream in(confFile);
  bool write=true;

  // Configuration variables
  float dummy = 80;

  if (in) {
    lti::lispStreamHandler lsh;
    lsh.use(in);
    write=!lti::read(lsh,"dummy",dummy);
  }
  if (write) {
    // something went wrong loading the data, so just write again to fix
    // the errors
    std::ofstream out(confFile);
    lti::lispStreamHandler lsh;
    lsh.use(out);
    lti::write(lsh,"dummy",dummy);
    out<<std::endl;
  }

  lti::channel8 res;
  res.resize(img.rows(), img.columns(), 0);

  lti::viewer2D view("Transformed");
  lti::viewer2D::interaction action;
  lti::ipoint pos;

  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double,std::ratio<1,1000> > elapsed_seconds;


  double acc_samp=0;
  std::cout << " , dokladal(ms)" << std::endl;
  for (int wsize =1; wsize<23; wsize+=2){

    acc_samp=0;
    for(int i=0; i<1; i++){
      start = std::chrono::system_clock::now();
      dokladal(res,img,wsize);
      end = std::chrono::system_clock::now();
      elapsed_seconds = end - start;
      acc_samp+=elapsed_seconds.count();
    }
    std::cout << " , " << acc_samp/100 << std::endl;
  }

  bool showTransformed= true;
  do {
    // Apply algorithm;

     //Show
     if(showTransformed)
         view.show(res);
     else
        view.show(img);

    if(view.waitButtonReleased(action, pos))
    {
        showTransformed = !showTransformed;
    }
  } while(action.action != lti::viewer2D::Closed);

  return EXIT_SUCCESS;
}
