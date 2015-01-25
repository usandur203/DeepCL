// Copyright Hugh Perkins 2014 hughperkins at gmail
//
// This Source Code Form is subject to the terms of the Mozilla Public License, 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <stdexcept>
#include <string>
#include <iostream>

#include "MyRandom.h"
#include "ActivationFunction.h"
#include "LayerMaker.h"
#include "stringhelper.h"
#include "OpenCLHelper.h"

#define VIRTUAL virtual

class Layer {
public:
//    int batchStart;
//    int batchEnd;

    Layer *previousLayer;
    Layer *nextLayer;
//    const int numPlanes;
//    const int boardSize;
//    const bool biased;
//    ActivationFunction const *const activationFunction;
//    const int upstreamBoardSize;
//    const int upstreamNumPlanes;
    const int layerIndex;
//    bool weOwnResults;

//    const int boardSizeSquared;
//    const int upstreamBoardSizeSquared;

//    int batchSize;

//    virtual bool needErrorsBackprop() = 0;

    // results structured like [imageid][outputplane][outputrow][outputcol]
//    inline int getResultIndex( int n, int plane, int row, int col ) const {
//        return ( ( ( n * numPlanes ) + plane ) * boardSize + row ) * boardSize + col;
//    }
//    inline float getResult( int n, int plane, int row, int col ) const {
//        return results[getResultIndex( n, plane,row,col)];
//    }
//    inline int getResultsSizePerExample() const {
//        return numPlanes * boardSize * boardSize;
//    }
    virtual float * getResults() = 0;

    // [[[cog
    // import cog_addheaders
    // cog_addheaders.add()
    // ]]]

    Layer( Layer *previousLayer, LayerMaker const*maker );
    VIRTUAL ~Layer();
    VIRTUAL void setBatchSize( int batchSize );
    VIRTUAL bool providesErrorsForUpstreamWrapper() const;
    VIRTUAL float *getErrorsForUpstream();
    VIRTUAL CLWrapper *getErrorsForUpstreamWrapper();
    VIRTUAL bool getBiased() const;
    VIRTUAL bool hasResultsWrapper() const;
    VIRTUAL CLWrapper *getResultsWrapper();
    VIRTUAL ActivationFunction const*getActivationFunction();
    VIRTUAL int getResultsSize() const;
    VIRTUAL int getOutputCubeSize() const;
    VIRTUAL int getOutputPlanes() const;
    VIRTUAL int getOutputBoardSize() const;
    VIRTUAL void propagate();
    VIRTUAL void print();
    VIRTUAL void initWeights( float const*weights );
    VIRTUAL void initBiasWeights( float const *biasWeights );
    VIRTUAL void printWeightsAsCode() const;
    VIRTUAL void printBiasWeightsAsCode() const;
    VIRTUAL void printWeights();
    VIRTUAL void printOutput() const;
    VIRTUAL void backProp( float learningRate );
    VIRTUAL int getWeightsSize() const;
    VIRTUAL int getBiasWeightsSize() const;
    VIRTUAL int getPersistSize() const;
    VIRTUAL void persistToArray(float *array);
    VIRTUAL void unpersistFromArray(float const*array);
    VIRTUAL void setWeights(float *weights, float *biasWeights);
    VIRTUAL float const *getWeights() const;
    VIRTUAL float *getWeights();
    VIRTUAL float const*getBiasWeights() const;
    VIRTUAL std::string asString() const;

    // [[[end]]]

};

std::ostream &operator<<(std::ostream&os, Layer const*layer );
