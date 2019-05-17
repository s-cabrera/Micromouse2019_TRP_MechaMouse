void maze_code(){
  unsigned int choice;
  randomSeed(millis()+1);
 choice = random(1);
  
   if( (centerSensor > minmium) && (leftsensor < minmium) && (rightsnesor < minmium)  ){
    
    if(choice = 1){
      turnright();
    }
    if(choice = 0){
      turnleft();
    }
  }
  else if(centerSensor < minmium) && (leftsensor < minmium) && (rightsnesor > minmium){
    if(choice = 1){
      gostraight;
    }
    if(choice = 0){
      turnleft();
    }
  }

      else if(centerSensor < minmium) && (leftsensor > minmium) && (rightsnesor < minmium){
    if(choice = 1){
      turnright();
    }
    if(choice = 0){
      gostraight();
    }
  }
  else if ((centerSensor > minmium) && (leftsensor < minmium) && (rightsnesor > minmium)  ){
    reverse();
  }
  }


