#include "ofApp.h"

using namespace std;

vector <int> unpassableLayer;
vector <int> foregroundLayer;

int scanMode = 0;
int tmpInt = 0;
int counter = 0;
int l = 0;
int jumpCount = 0;
int yPreviousVelocity = 0;
bool arrowKeyPressed = false;

//--------------------------------------------------------------
void ofApp::setup(){
	//physics initalization stuff
	box2d.init();//  x   y
	box2d.setGravity(0, 10);
	box2d.setFPS(60.0);
	box2d.registerGrabbing();//idk what this does
	t = 0; //for a timer
    
    ofSetWindowShape(400, 400);//sets window size
	tileset.load("omegateam.png");//loads tileset image
	
	//sets level size, 
	//this will be automatically read off of the
	// level files in the future
	levelSizeX = 20;
    levelSizeY = 20;
    
    for(int y = 0; y <= tileset.getHeight()/tileSize; y++){
        for(int x = 0; x <= tileset.getWidth()/tileSize; x++){
            
            //create temporary image placeholder
            //save sprite sheet image into it
            ofImage tmp = tileset;
            //crop image to 16 by 16 size
            tmp.crop(x*tileSize, y*tileSize, tileSize, tileSize);
			//push it to tiles vector
            tiles.push_back(tmp);
            
        }
    }
    //open level text file
    ifstream file("bin/data/crappyCastle.txt");
    
    if(file.is_open()){
        //returns each line as string 'line'
        while( getline(file,line)){
            
			cout << endl;
			//clear buffer
			buffer = "";
			//scanmode 1 = reading level data
			if(scanMode == 1){
				//read each char in line
				for(int i = 0; i <= line.length(); i++){
                
					buffer+= line[i];//add char to buffer
						
					if(buffer.back() == ','){//if the end of the buffer is a comma
						buffer.pop_back();//remove comma
						tmpInt = ofToInt(buffer);//convert buffer to int
						unpassableLayer.push_back(tmpInt); //push to level vect
						buffer = ""; //clear vector
					}
				}						
			}
			//scanmode 0 = waiting for layer
			else if(line == "[layer]"){
				
				scanMode = 1;
				buffer = "";
				
			}
			else if(line == ""){
				
		//		layer.push_back(layer());
				scanMode = 0;
				
			}
		}
		 file.close();  //closes file   
   
	}
	
	counter = 0;
	
	//create physics layer
	for (int y = 0; y <= levelSizeY; y++){
		for(int x = 0; x <= levelSizeX; x++){
			
			
			if(unpassableLayer[counter] != 0){//if tile is not empty space
				boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect)); //add physics box shape to physics vector
				boxes.back().get()->setPhysics(3.0, 0.53, 0.1);//set physics properties of boxes
				boxes.back().get()->setup(box2d.getWorld(), 9+x*tileSize, 9+y*tileSize, tileSize, tileSize);//setup
				boxes.back().get()->body->SetType(b2_staticBody);//make still
			}
			counter++;//increment tile counter
			
		}
	}
	
	cout << unpassableLayer[t] << endl;//print tile value
 
	t++;
	
		player.setPhysics(100.0, -20.0, 1.0);//set physics settings for player
		player.setup(box2d.getWorld(), 50, 100, tileSize, tileSize);
		
}
    


//--------------------------------------------------------------
void ofApp::update(){

	box2d.update();//updates physics world
   
	if (yPreviousVelocity > 0 && player.getVelocity().y < 0){
		jumpCount = 0;
		cout << "Ground" << endl;
	}
	
	yPreviousVelocity = player.getVelocity().y;

}

//--------------------------------------------------------------
void ofApp::draw(){
        
    counter = 0;
    //draw level
		for(int y = 0; y < levelSizeY; y++){
			for(int x = 0; x < levelSizeX+1; x++){
			
				
				int a = unpassableLayer[counter];
				a--;
			
				if(a > -1){
					//draw tile 
					tiles[a].draw(x*tileSize, y*tileSize);
					ofNoFill();
					ofSetColor(255);
				//	ofDrawRectangle(x*tileSize, y*tileSize, tileSize, tileSize);
				
				}
				//cout << layer[counter] << endl;
	
				counter++;


			}

		}
		
       tiles[t].draw(mouseX, mouseY);
       
       for(int i = 0; i < boxes.size(); i++){
		//boxes[i].get()->draw();//draw physics boundaries
	   }
	   
	   ofDrawRectangle(player.getPosition().x-tileSize, player.getPosition().y-tileSize, tileSize*2, tileSize*2);
	   //draw player sprite
		player.draw();
		
		
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
		
		//jump 
	if(key == ' ' && player.getVelocity().y < 2 && player.getVelocity().y > -0.08){
		if(jumpCount < 1){
			player.setVelocity(player.getVelocity().x, -5);
			jumpCount=1;
		}
	}
	//left right move
	if(key == OF_KEY_RIGHT && jumpCount < 1){
		arrowKeyPressed = true;
		player.setVelocity(3, player.getVelocity().y);
	}
	if(key == OF_KEY_LEFT && jumpCount < 1){
		arrowKeyPressed = false;
		player.setVelocity(-3, player.getVelocity().y);
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	if(key == OF_KEY_LEFT || key == OF_KEY_RIGHT){
		arrowKeyPressed = false;
	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    mouseX = x;
    mouseY = y;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
   
	
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
