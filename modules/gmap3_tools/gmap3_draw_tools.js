/* 
 * Add a drawing controler to the maps
 */

(function ($) {
  function gmap3ToolsCreateDrawTools(mapElement, drawSettings) {
    if (drawSettings.mapId === null) {
      alert(Drupal.t('gmap3_tools error: Map id element is not defined.'));
      return null;
    }
    
    var drawingManager = new google.maps.drawing.DrawingManager(
                                         drawSettings.drawingManagerOptions);
    //var drawingManager = new google.maps.drawing.DrawingManager();
    
    drawingManager.setMap(mapElement);
    
    google.maps.event.addListener(drawingManager,
                                  "overlaycomplete",
                                  function(event){
      drawingManager.setOptions({drawingMode:null});
      $(drawSettings.formElements.typeElement).val(event.type);
      
      var wkt = overlayToWkt(event);

      $(drawSettings.formElements.pointsElement).text(wkt);
    })
  }
  
  function overlayToWkt(overlayEvent){
    var wkt = "";
      
    switch (overlayEvent.type){
      case "polygon":
        wkt += "POLYGON (";
        var LinearRings = overlayEvent.overlay.getPaths().getArray();
        LinearRings.forEach(function(linearRing, lrIndex){
          wkt += "(";
          linearRing.forEach(function(point, pntIndex){
            wkt += point.lng().toString() + " " + point.lat().toString();
            
            //
            if (linearRing.getLength() -1 != pntIndex){
              wkt += ", ";
            }
          });
          wkt += ")";

          // insert , when needed
          if (LinearRings.length -1 != lrIndex) {
             wkt += ", ";
          }
        });

        wkt += ")";
        break;
      default:
        break;
      
      
    }
     console.log(wkt);
    return wkt;
  }
  
  /**
   * Attach gmap3_tools_draw.
   */
  Drupal.behaviors.gmap3_tools_draw = {
    attach: function (context, settings) {
      // Create all defined google maps.
      if (settings.gmap3_tools.draw === undefined) {
        return;
      }
      
      $.each(settings.gmap3_tools.draw, function(i, drawSettings) {
        // choose the current map according to the map ID
        var mapElement = $('#' + drawSettings.mapId, context);
        
        // avoid cases that the map has the drawing settings or therer isn't element
        if (mapElement.length === 0 || 
            mapElement.hasClass('gmap3-draw-tools-processed')) {
          return;
        }
        
        mapElement.addClass('gmap3-draw-tools-processed');
        
        //
        var gmap = settings.gmap3_tools.maps.filter(function(element){
          return element.mapId === drawSettings.mapId;
        })[0].mapObject;
        
        gmap3ToolsCreateDrawTools(gmap, drawSettings);
      });
    }
  };
  
})(jQuery);