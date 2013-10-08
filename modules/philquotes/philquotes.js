var Philquotes = {};

//add dynamically Next button after phiqoute dom object
if (Drupal.jsEnabled) {
    $(document).ready(
        function(){
            $("#philquotes-origin").after("<a id='next-quote-url'>Next &raquo;</a>").
                next().click(Philquotes.randQuote);
        }
        );


   /**
    * A function to fetch quotes from the server, and display in the
    * designated area.
    */
    Philquotes.randQuote = function() {
        //use jQuery axjax call function
        $.get(
          //use json url specified in setting parameters
          Drupal.settings.philquotes.json_url, 
          function(data) {
            //parse JSON   
            myQuote = Drupal.parseJson(data);
            
            if(!myQuote.status || myQuote.status == 0) {
                //if OK - repaint quote divs
                $("#philquotes-origin").text(myQuote.quote.origin);
                $("#philquotes-text").text(myQuote.quote.text);
            }
          }); // End inline function
    }


}

