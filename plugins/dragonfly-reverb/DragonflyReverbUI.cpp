/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2015 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#include "DistrhoUI.hpp"
#include "DragonflyReverbUI.hpp"
#include "DragonflyReverbArtwork.hpp"
#include "DistrhoPluginInfo.h"
#include "NotoSans_Regular.ttf.hpp"
#include <array>
#include <vector>
#include <math.h>
#include <string>

START_NAMESPACE_DISTRHO

namespace Art = DragonflyReverbArtwork;
using DGL::Color;

static const int knobx[] = {20, 108, 195};
static const int knoby[] = {25, 135, 245};

// -----------------------------------------------------------------------------------------------------------
DragonflyReverbUI::DragonflyReverbUI()
  : UI ( Art::backgroundWidth, Art::backgroundHeight ),
    fImgBackground ( Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, GL_BGR ),
    fImgTabOff ( Art::tab_offData, Art::tab_offWidth, Art::tab_offHeight, GL_BGR ),
    fImgTabOn ( Art::tab_onData, Art::tab_onWidth,Art::tab_onHeight, GL_BGR )
{
  // text
  fNanoFont  = fNanoText.createFontFromMemory ( "notosans", font_notosans::notosans_ttf, font_notosans::notosans_ttf_size, false );
  fNanoText.fontFaceId ( fNanoFont );

  fKnobSize = new ImageKnob ( this,
                              Image ( Art::knobData, Art::knobWidth, Art::knobHeight, GL_BGRA ) );
  fKnobSize->setId ( paramSize );
  fKnobSize->setAbsolutePos ( knobx[1], knoby[0] );
  fKnobSize->setRange ( params[paramSize].range_min, params[paramSize].range_max );
  fKnobSize->setRotationAngle ( 300 );
  fKnobSize->setCallback ( this );

  fKnobPredelay = new ImageKnob ( this,
                                  Image ( Art::knobData, Art::knobWidth, Art::knobHeight, GL_BGRA ) );
  fKnobPredelay->setId ( paramPredelay );
  fKnobPredelay->setAbsolutePos ( knobx[0], knoby[0] );
  fKnobPredelay->setRange ( params[paramPredelay].range_min, params[paramPredelay].range_max );
  fKnobPredelay->setRotationAngle ( 300 );
  fKnobPredelay->setCallback ( this );

  fKnobDiffuse = new ImageKnob ( this,
                                 Image ( Art::knobData, Art::knobWidth, Art::knobHeight, GL_BGRA ) );
  fKnobDiffuse->setId ( paramDiffuse );
  fKnobDiffuse->setAbsolutePos ( knobx[2], knoby[0] );
  fKnobDiffuse->setRange ( params[paramDiffuse].range_min, params[paramDiffuse].range_max );
  fKnobDiffuse->setRotationAngle ( 300 );
  fKnobDiffuse->setCallback ( this );

  fKnobLow_cut = new ImageKnob ( this,
                                 Image ( Art::knobData, Art::knobWidth, Art::knobHeight, GL_BGRA ) );
  fKnobLow_cut->setId ( paramLow_cut );
  fKnobLow_cut->setAbsolutePos ( knobx[0], knoby[2] );
  fKnobLow_cut->setRange ( params[paramLow_cut].range_min, params[paramLow_cut].range_max );
  fKnobLow_cut->setRotationAngle ( 300 );
  fKnobLow_cut->setCallback ( this );

  fKnobLow_xover = new ImageKnob ( this,
                                   Image ( Art::knobData, Art::knobWidth, Art::knobHeight, GL_BGRA ) );
  fKnobLow_xover->setId ( paramLow_xover );
  fKnobLow_xover->setAbsolutePos ( knobx[1], knoby[2] );
  fKnobLow_xover->setRange ( params[paramLow_xover].range_min, params[paramLow_xover].range_max );
  fKnobLow_xover->setRotationAngle ( 300 );
  fKnobLow_xover->setCallback ( this );

  fKnobLow_mult = new ImageKnob ( this,
                                  Image ( Art::knobData, Art::knobWidth, Art::knobHeight, GL_BGRA ) );
  fKnobLow_mult->setId ( paramLow_mult );
  fKnobLow_mult->setAbsolutePos ( knobx[2], knoby[2] );
  fKnobLow_mult->setRange ( params[paramLow_mult].range_min, params[paramLow_mult].range_max );
  fKnobLow_mult->setRotationAngle ( 300 );
  fKnobLow_mult->setCallback ( this );

  fKnobHigh_cut = new ImageKnob ( this,
                                  Image ( Art::knobData, Art::knobWidth, Art::knobHeight, GL_BGRA ) );
  fKnobHigh_cut->setId ( paramHigh_cut );
  fKnobHigh_cut->setAbsolutePos ( knobx[0], knoby[1] );
  fKnobHigh_cut->setRange ( params[paramHigh_cut].range_min, params[paramHigh_cut].range_max );
  fKnobHigh_cut->setRotationAngle ( 300 );
  fKnobHigh_cut->setCallback ( this );

  fKnobHigh_xover = new ImageKnob ( this,
                                    Image ( Art::knobData, Art::knobWidth, Art::knobHeight, GL_BGRA ) );
  fKnobHigh_xover->setId ( paramHigh_xover );
  fKnobHigh_xover->setAbsolutePos ( knobx[1], knoby[1] );
  fKnobHigh_xover->setRange ( params[paramHigh_xover].range_min, params[paramHigh_xover].range_max );
  fKnobHigh_xover->setRotationAngle ( 300 );
  fKnobHigh_xover->setCallback ( this );

  fKnobHigh_mult = new ImageKnob ( this,
                                   Image ( Art::knobData, Art::knobWidth, Art::knobHeight, GL_BGRA ) );
  fKnobHigh_mult->setId ( paramHigh_mult );
  fKnobHigh_mult->setAbsolutePos ( knobx[2], knoby[1] );
  fKnobHigh_mult->setRange ( params[paramHigh_mult].range_min, params[paramHigh_mult].range_max );
  fKnobHigh_mult->setRotationAngle ( 300 );
  fKnobHigh_mult->setCallback ( this );

  // sliders


  fSliderDry_level = new ImageSlider ( this,
                                       Image ( Art::sliderData, Art::sliderWidth, Art::sliderHeight, GL_BGRA ) );
  fSliderDry_level->setId ( paramDry_level );
  fSliderDry_level->setStartPos ( 760, 32 );
  fSliderDry_level->setEndPos ( 760, 300 );
  fSliderDry_level->setRange ( 0.0f, 100.0f );
  fSliderDry_level->setInverted ( true );
  fSliderDry_level->setCallback ( this );

  fSliderEarly_level = new ImageSlider ( this,
                                         Image ( Art::sliderData, Art::sliderWidth, Art::sliderHeight, GL_BGRA ) );
  fSliderEarly_level->setId ( paramEarly_level );
  fSliderEarly_level->setStartPos ( 800, 32 );
  fSliderEarly_level->setEndPos ( 800, 300 );
  fSliderEarly_level->setRange ( 0.0f, 100.0f );
  fSliderEarly_level->setInverted ( true );
  fSliderEarly_level->setCallback ( this );

  fSliderLate_level = new ImageSlider ( this,
                                        Image ( Art::sliderData, Art::sliderWidth, Art::sliderHeight, GL_BGRA ) );
  fSliderLate_level->setId ( paramLate_level );
  fSliderLate_level->setStartPos ( 840, 32 );
  fSliderLate_level->setEndPos ( 840, 300 );
  fSliderLate_level->setRange ( 0.0f, 100.0f );
  fSliderLate_level->setInverted ( true );
  fSliderLate_level->setCallback ( this );

  // rectangles for displaytabs
  rectTabResponse.setPos ( 315, 85 );
  rectTabResponse.setSize ( Art::tab_onWidth, Art::tab_onHeight );
  rectTabPrograms.setPos ( 405, 85 );
  rectTabPrograms.setSize ( Art::tab_onWidth, Art::tab_onHeight );
  rectTabAbout.setPos ( 495, 85 );
  rectTabAbout.setSize ( Art::tab_onWidth, Art::tab_onHeight );

  // rectangles for display
  rectDisplay.setPos ( 285,110 );
  rectDisplay.setSize ( 450,210 );

  spectrogram = new Spectrogram(this, &fNanoText, &rectDisplay);
  spectrogram->setAbsolutePos (285, 110);

  // rectangles for programs
  for ( int i = 0; i < 3; ++i ) // 3 columns
    {
      int startx = 290, starty = 115;
      int height = ( rectDisplay.getHeight()-10 ) / 8;
      int width = ( rectDisplay.getWidth()-10 ) /3;

      for ( int j=0; j < 8; ++j ) // 8 rows
        {
          int programIndex = j + ( i * 8 );
          int x = startx + i * width;
          int y = starty + height * j;
          rectPrograms[programIndex].setPos ( x,y );
          rectPrograms[programIndex].setSize ( width,height );
        }
    }

  // rectangles for sliders
  rectSliders[0].setPos ( 762,32 );
  rectSliders[0].setSize ( 26,271 );
  rectSliders[1].setPos ( 802,32 );
  rectSliders[1].setSize ( 26,271 );
  rectSliders[2].setPos ( 842,32 );
  rectSliders[2].setSize ( 26,271 );
}

/**
   A parameter has changed on the plugin side
   This is called by the host to inform the UI about parameter changes.
 */
void DragonflyReverbUI::parameterChanged ( uint32_t index, float value )
{
  switch ( index )
    {
      // sliders

    case paramDry_level:
      fSliderDry_level->setValue ( value );
      break;

    case paramEarly_level:
      fSliderEarly_level->setValue ( value );
      break;

    case paramLate_level:
      fSliderLate_level->setValue ( value );
      break;

      // knobs

    case paramSize:
      fKnobSize->setValue ( value );
      break;

    case paramPredelay:
      fKnobPredelay->setValue ( value );
      break;

    case paramDiffuse:
      fKnobDiffuse->setValue ( value );
      break;

    case paramLow_cut:
      fKnobLow_cut->setValue ( value );
      break;

    case paramLow_xover:
      fKnobLow_xover->setValue ( value );
      break;

    case paramLow_mult:
      fKnobLow_mult->setValue ( value );
      break;

    case paramHigh_cut:
      fKnobHigh_cut->setValue ( value );
      break;

    case paramHigh_xover:
      fKnobHigh_xover->setValue ( value );
      break;

    case paramHigh_mult:
      fKnobHigh_mult->setValue ( value );
      break;

    }

    spectrogram->setParameterValue(index, value);
}

/* ----------------------------------------------------------------------------------------------------------
 * Widget Callbacks
 *----------------------------------------------------------------------------------------------------------*/

void DragonflyReverbUI::imageKnobDragStarted ( ImageKnob* knob )
{
  editParameter ( knob->getId(), true );
}

void DragonflyReverbUI::imageKnobDragFinished ( ImageKnob* knob )
{
  editParameter ( knob->getId(), false );
}

void DragonflyReverbUI::imageKnobValueChanged ( ImageKnob* knob, float value )
{
  setParameterValue ( knob->getId(),value );
  spectrogram->setParameterValue ( knob->getId(), value );
}

void  DragonflyReverbUI::imageSliderDragStarted ( ImageSlider* slider )
{
  editParameter ( slider->getId(), true );
}

void  DragonflyReverbUI::imageSliderDragFinished ( ImageSlider* slider )
{
  editParameter ( slider->getId(), false );
}

void  DragonflyReverbUI::imageSliderValueChanged ( ImageSlider* slider, float value )
{
  int SliderID = slider->getId();
  setParameterValue ( SliderID,value );
  spectrogram->setParameterValue ( SliderID, value );
}

void DragonflyReverbUI::programLoaded ( uint32_t index )
{
  currentProgram = index;
  const float *preset = presets[index].params;
  fSliderDry_level->setValue ( preset[paramDry_level] );
  fSliderEarly_level->setValue ( preset[paramEarly_level] );
  fSliderLate_level->setValue ( preset[paramLate_level] );
  fKnobSize->setValue ( preset[paramSize] );
  fKnobPredelay->setValue ( preset[paramPredelay] );
  fKnobDiffuse->setValue ( preset[paramDiffuse] );
  fKnobLow_cut->setValue ( preset[paramLow_cut] );
  fKnobLow_xover->setValue ( preset[paramLow_xover] );
  fKnobLow_mult->setValue ( preset[paramLow_mult] );
  fKnobHigh_cut->setValue ( preset[paramHigh_cut] );
  fKnobHigh_xover->setValue ( preset[paramHigh_xover] );
  fKnobHigh_mult->setValue ( preset[paramHigh_mult] );
  for ( uint32_t i = 0; i < paramCount; i++ ) {
    setParameterValue ( i, preset[i] );
    spectrogram->setParameterValue(i, preset[i]);
  }
}

bool DragonflyReverbUI::onMouse ( const MouseEvent& ev )
{
  // display
  if ( ev.button != 1 )
    return false;
  if ( ev.press )
    {
      if ( rectDisplay.contains ( ev.pos ) )
        {
          switch ( currentDisplayMode )
            {
            case displayResponse:
              return false;
              break;


            case displayPrograms:
              for ( int i = 0; i < 24; i++ )
                {
                  if ( rectPrograms[i].contains ( ev.pos ) )
                    {
                      currentProgram = i;

                      programLoaded ( currentProgram );
                      currentDisplayMode = displayResponse;
                      repaint();
                    } // end if
                } // end for

              break;

            case displayAbout:
              currentDisplayMode = displayResponse;
              repaint();

              break;
            } // end switch
          return false;
        } // end if rectDisplay

      // check for clicks on tabs

      if ( rectTabResponse.contains ( ev.pos ) )
        {
          currentDisplayMode = displayResponse;
          repaint();
          return true;
        }

      if ( rectTabPrograms.contains ( ev.pos ) )
        {
          currentDisplayMode = displayPrograms;
          repaint();
          return true;
        }

      if ( rectTabAbout.contains ( ev.pos ) )
        {
          currentDisplayMode = displayAbout;
          repaint();
          return true;
        }

    } // end if ev.press
  return false;
}

void DragonflyReverbUI::onDisplay()
{
  fImgBackground.draw();
  float r,g,b;
  // wipe display
  r = 80.0f / 256.0f;
  g = 80.0f / 256.0f;
  b = 80.0f / 256.0f;
  // rectangle to wipe
  glColor4f ( r, g, b, 1.0f );
  rectDisplay.draw();

  // print parameters
  fNanoText.beginFrame ( this );
  fNanoText.fontSize ( 16 );
  fNanoText.textAlign ( NanoVG::ALIGN_CENTER|NanoVG::ALIGN_MIDDLE );

  r = 230.0f / 256;
  g = 230.0f / 256;
  b = 230.0f / 256;
  fNanoText.fillColor ( Color ( r, g, b ) );

  char strBuf[32+1];
  strBuf[32] = '\0';

  float xstart = 20.0f, ystart= 92.0f;
  float xoffset = 88.0f, yoffset = 110.0f;


  std::snprintf ( strBuf, 32, "%4.2f ms", fKnobPredelay->getValue() );
  fNanoText.textBox ( xstart             , ystart , 60.0f, strBuf, nullptr );
  std::snprintf ( strBuf, 32, "%i Hz", int ( fKnobHigh_cut->getValue() ) );
  fNanoText.textBox ( xstart             , ystart + yoffset ,60.0f, strBuf, nullptr );
  std::snprintf ( strBuf, 32, "%4.2f Hz", fKnobLow_cut->getValue() );
  fNanoText.textBox ( xstart             , ystart + yoffset*2 ,60.0f, strBuf, nullptr );

  std::snprintf ( strBuf, 32, " %4.2f m", fKnobSize->getValue() );
  fNanoText.textBox ( xstart + xoffset   , ystart , 60.0f, strBuf, nullptr );
  std::snprintf ( strBuf, 32, " %i Hz", int ( fKnobHigh_xover->getValue() ) );
  fNanoText.textBox ( xstart + xoffset   , ystart + yoffset, 60.0f, strBuf, nullptr );
  std::snprintf ( strBuf, 32, "%4.2f Hz", fKnobLow_xover->getValue() );
  fNanoText.textBox ( xstart + xoffset   , ystart + yoffset*2, 65.0f, strBuf, nullptr );


  std::snprintf ( strBuf, 32, "%i %%", int ( fKnobDiffuse->getValue() ) );
  fNanoText.textBox ( xstart  + xoffset*2 , ystart , 60.0f, strBuf, nullptr );
  std::snprintf ( strBuf, 32, "%4.2f X", fKnobHigh_mult->getValue() );
  fNanoText.textBox ( xstart  + xoffset*2 , ystart + yoffset, 60.0f, strBuf, nullptr );
  std::snprintf ( strBuf, 32, "%4.2f X", fKnobLow_mult->getValue() );
  fNanoText.textBox ( xstart  + xoffset*2 , ystart + yoffset*2, 60.0f, strBuf, nullptr );

  std::snprintf ( strBuf, 32, "%i %%", int ( fSliderDry_level->getValue() ) );
  fNanoText.textBox ( 760 - 2  , 314 , 35.0f, strBuf, nullptr );
  std::snprintf ( strBuf, 32, "%i %%", int ( fSliderEarly_level->getValue() ) );
  fNanoText.textBox ( 800 - 2, 314, 35.0f, strBuf, nullptr );
  std::snprintf ( strBuf, 32, "%i %%", int ( fSliderLate_level->getValue() ) );
  fNanoText.textBox ( 840 - 2, 314 , 35.0f, strBuf, nullptr );

  // print lables;
  r = 205.0f / 256;
  g = 241.0f / 256;
  b = 255.0f / 256;
  fNanoText.fillColor ( Color ( r, g, b ) );
  fNanoText.fontSize ( 18 );
  int labelX[6]= {20,105,194,760,800,840};
  int labelY[4]= {18,128,238,20};
  float labelWidth = 65.0f;
  fNanoText.textBox ( labelX[0], labelY[0] , labelWidth, "Pre-Delay", nullptr );
  fNanoText.textBox ( labelX[1], labelY[0] , labelWidth, "Size", nullptr );
  fNanoText.textBox ( labelX[2], labelY[0] , labelWidth, "Diffuse", nullptr );
  fNanoText.textBox ( labelX[0], labelY[1] , labelWidth, "High Cut", nullptr );
  fNanoText.textBox ( labelX[1], labelY[1] , labelWidth, "High Cross", nullptr );
  fNanoText.textBox ( labelX[2], labelY[1] , labelWidth, "High Multi", nullptr );
  fNanoText.textBox ( labelX[0], labelY[2] , labelWidth, "Low Cut", nullptr );
  fNanoText.textBox ( labelX[1], labelY[2] , labelWidth, "Low Cross", nullptr );
  fNanoText.textBox ( labelX[2], labelY[2] , labelWidth, "Low Multi", nullptr );
  fNanoText.textBox ( labelX[3], labelY[3] , 30 , "Dry", nullptr );
  fNanoText.textBox ( labelX[4], labelY[3] , 30, "Early", nullptr );
  fNanoText.textBox ( labelX[5], labelY[3] , 30, "Late", nullptr );

  //fNanoText.textBox( 325 , 90 , 30, "Repsonse", nullptr);

  fNanoText.endFrame();

  //draw faders
  r = 82.0f/255.f;
  g = 148.0f/255.f;
  b = 88.0f/255.f;
  glColor4f ( r, g, b, 1.0f );
  float dry = ( float ( fSliderDry_level->getValue() ) / 100 ) * 271;
  float early = ( float ( fSliderEarly_level->getValue() ) / 100 ) * 271;
  float late = ( float ( fSliderLate_level->getValue() ) / 100 ) * 271;

  rectSliders[0].setHeight ( dry + 0.5f );
  rectSliders[0].setY ( 32+271-dry+ 0.5f );

  rectSliders[1].setHeight ( early + 0.5f );
  rectSliders[1].setY ( 32+271-early +0.5 );

  rectSliders[2].setHeight ( late +0.5f );
  rectSliders[2].setY ( 32+271-late + 0.5f );

  if ( int ( dry ) > 1 )
    rectSliders[0].draw();
  if ( int ( early ) > 1 )
    rectSliders[1].draw();
  if ( int ( late ) > 1 )
    rectSliders[2].draw();


  switch ( int ( currentDisplayMode ) ) {
    case displayResponse:
    {
      spectrogram->show();

      // draw tabs
      glColor4f ( 1.0f,1.0f,1.0f,1.0f ); // reset colour

      fImgTabOn.drawAt ( 315,85 );
      fImgTabOff.drawAt ( 405,85 );
      fImgTabOff.drawAt ( 495,85 );

      break;
    }

    case displayPrograms:
    {
      spectrogram->hide();
      fNanoText.beginFrame ( this );
      fNanoText.fontSize ( 18 );
      fNanoText.textAlign ( NanoVG::ALIGN_CENTER|NanoVG::ALIGN_MIDDLE );

      r = 230.0f / 256;
      g = 230.0f / 256;
      b = 230.0f / 256;
      fNanoText.fillColor ( Color ( r, g, b ) );

      char strBuf[32+1];
      strBuf[32] = '\0';
      for ( int i = 0; i < 24; i++ )
        {
          int x = rectPrograms[i].getX();
          int y = rectPrograms[i].getY();
          int w = rectPrograms[i].getWidth();
          int h = rectPrograms[i].getHeight();
          std::snprintf ( strBuf, 32, "%s", presets[i].name );
          fNanoText.textBox ( x, y + ( h/2 ), w, strBuf, nullptr );
        }
      fNanoText.endFrame();

      // draw box around current program
      // r = 230.0f / 256;
      // g = 230.0f / 256;
      // b = 230.0f / 256;
      glColor4f ( r,g,b ,1.0f );
//       for ( int i = 0 ; i < 24 ; i++ )
// 	rectPrograms[i].drawOutline();
//
      // rectPrograms[currentProgram].drawOutline();

      // draw tabs
      glColor4f ( 1.0f,1.0f,1.0f,1.0f );
      fImgTabOff.drawAt ( 315,85 );
      fImgTabOn.drawAt ( 405,85 );
      fImgTabOff.drawAt ( 495,85 );


      break;
    }
    case displayAbout:
    {
      spectrogram->hide();
      fNanoText.beginFrame ( this );
      fNanoText.fontSize ( 18 );
      fNanoText.textAlign ( NanoVG::ALIGN_LEFT|NanoVG::ALIGN_TOP );

      r = 230.0f / 256;
      g = 230.0f / 256;
      b = 230.0f / 256;
      fNanoText.fillColor ( Color ( r, g, b ) );

      int x = rectDisplay.getX() + 10;
      int y = rectDisplay.getY() + 5;
      int w = rectDisplay.getWidth() - 20;

      fNanoText.textBox ( x, y , w ,
        "A hall-style reverb based on algorithms from Freeverb3\n"
        "License: GPL 3+ (https://www.gnu.org/licenses/gpl-3.0.en.html)\n\n"
        "Michael Willis - Initial concept, plugin, and spectrogram\n\n"
        "Rob van dev Berg - Graphical interface\n\n"
        "Teru Kamogashira - Freeverb3\n\n"
        "Thanks to Filipe \"falkTX\" Coelho for developing the excellent Distrho Plugin Framework and providing plenty of advice."
        , nullptr );
      fNanoText.endFrame();
      // draw tabs
      glColor4f ( 1.0f,1.0f,1.0f,1.0f );
      fImgTabOff.drawAt ( 315,85 );
      fImgTabOff.drawAt ( 405,85 );
      fImgTabOn.drawAt ( 495,85 );

      break;
    }

  } // end switch

  // draw labels on tabs
  fNanoText.beginFrame ( this );
  fNanoText.fontSize ( 18 );
  fNanoText.textAlign ( NanoVG::ALIGN_CENTER|NanoVG::ALIGN_MIDDLE );
  r = 205.0f / 256;
  g = 241.0f / 256;
  b = 255.0f / 256;
  fNanoText.fillColor ( Color ( r, g, b ) );
  float y = 85 + ( 22/2 );
  fNanoText.textBox ( 315.0f, y, 80.0f , "Response", nullptr );
  fNanoText.textBox ( 405.0f ,y, 80.0f , "Presets", nullptr );
  fNanoText.textBox ( 495.0f, y, 80.0f , "About"   , nullptr );
  fNanoText.endFrame();
}

void DragonflyReverbUI::uiIdle() {
  spectrogram->uiIdle();
}

/* ------------------------------------------------------------------------------------------------------------
 * UI entry point, called by DPF to create a new UI instance. */

UI* createUI()
{
  return new DragonflyReverbUI();
}

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
