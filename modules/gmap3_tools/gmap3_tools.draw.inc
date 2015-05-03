<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
function gmap3_tools_add_draw_tools($options) {
  // add the draw controller only for the first time
  static $init = FALSE;
  if (!$init) {
    $init = TRUE;
    // The drawing library of google maps
    drupal_add_js("http://maps.googleapis.com/maps/api/js?libraries=drawing", 
                  'external', array('scope' => 'footer'));
    // A customized js drawing file
    drupal_add_js(
        drupal_get_path('module', 'gmap3_tools') . '/gmap3_draw_tools.js', 
        array('scope' => 'footer'));
  }
  
  // Merge custom map options with defaults.
  $options = gmap3_tools_get_drawing_options($options);

  // Add map configuration options to js.
  drupal_add_js(array('gmap3_tools' => array('draw' => array($options))), 'setting');
}

/**
 * Returns the default JS settings for the map.
 *
 * @return array
 *   The default JS settings.
 */
function gmap3_tools_get_drawing_options($options) {
  static $defaults = array(
    // Map html element id.
    'mapId' => NULL,
    // Drawing options.
    'drawingManagerOptions' => array(
      // 
      'drawingControl' => true,
      // 
      'drawingMode' => null,
      // 
      //'drawingControlOptions' => array(
        //'drawingModes' => array(
        //  'MARKER', 'POLYLINE', 'RECTANGLE', 'CIRCLE', 'POLYGON'),
        //'position' => 'TOP_LEFT',      
      //),
      //
      'markerOptions' => array(
        'clickable' => true,
        'draggable' => true,
        'Opacity' => 1,
        'visible' => true,
      ),
      //
      'polygonOptions' => array(
        'clickable' => true,
        'draggable' => true,
        'editable' => true,
        'fillColor' => 'blue',
        'fillOpacity' => 0.3,
        'strokeColor' => 'black',
        'strokeOpacity' => 0,
        //'strokePosition' => 'CENTER',
        'strokeWeight' => 3,
        'visible' => true,
      ),
      //
      'circleOptions' => array(
        'clickable' => true,
        'draggable' => true,
        'editable' => true,
        'fillColor' => 'blue',
        'fillOpacity' => 0.2,
        'strokeColor' => 'black',
        'strokeOpacity' => 0,
        //'strokePosition' => 'CENTER',
        'strokeWeight' => 1,
        'visible' => true,
      ),
      //
      'polylineOptions' => array(
        'clickable' => true,
        'draggable' => true,
        'editable' => true,
        'fillColor' => 'blue',
        'fillOpacity' => 0.2,
        'strokeColor' => 'black',
        'strokeOpacity' => 0,
        //'strokePosition' => 'CENTER',
        'strokeWeight' => 1,
        'visible' => true,
      ),
      //
      'rectangleOptions' => array(
        'clickable' => true,
        'draggable' => true,
        'editable' => true,
        'fillColor' => 'blue',
        'fillOpacity' => 0.2,
        'strokeColor' => 'black',
        'strokeOpacity' => 0,
        //'strokePosition' => 'CENTER',
        'strokeWeight' => 1,
        'visible' => true,
      ),
    ),
  );

  return gmap3_tools_array_union_recursive($defaults, $options);
}

/**
 * Recursive union of two arrays. Works similar to + array operator but is also
 * taking care case when array values are also arrays.
 *
 * @param array $array1
 *   First array for union operation.
 * @param array $array2
 *   Second array for union operation.
 * @return array.
 *   Union result.
 */
//function gmap3_tools_array_union_recursive($array1, $array2) {
//  $union = $array1;
//  foreach ($array2 as $key => $value) {
//    if (array_key_exists($key, $union) && is_array($union[$key]) && is_array($value)) {
//      $union[$key] = gmap3_tools_array_union_recursive($union[$key], $value);
//    }
//    else {
//      $union[$key] = $value;
//    }
//  }
//  return $union;
//}