#include "InputMethodParser.h"

#include "InteractionBridge.h"

#include <iostream>

#include "InputMethodTokens.h"


#define KEYCODE_FOR_STRING(s,v) if(key==s)return v

#define CLONE_IF_EQUAL(test,s1,s2) else if(main[i]==test)CloneInto(&main,i,s1,s2)

namespace __RocEye__
{
	Uint16 InputMethodParser::GetKeycodeForStringKey(const std::string key) // needs to be upper cased before coming here
	{
		if(!key.size())
			return 0;
		
		KEYCODE_FOR_STRING("A",SDLK_a);
		KEYCODE_FOR_STRING("B",SDLK_b);
		KEYCODE_FOR_STRING("C",SDLK_c);
		KEYCODE_FOR_STRING("D",SDLK_d);
		KEYCODE_FOR_STRING("E",SDLK_e);
		KEYCODE_FOR_STRING("F",SDLK_f);
		KEYCODE_FOR_STRING("G",SDLK_g);
		KEYCODE_FOR_STRING("H",SDLK_h);
		KEYCODE_FOR_STRING("I",SDLK_i);
		KEYCODE_FOR_STRING("J",SDLK_j);
		KEYCODE_FOR_STRING("K",SDLK_k);
		KEYCODE_FOR_STRING("L",SDLK_l);
		KEYCODE_FOR_STRING("M",SDLK_m);
		KEYCODE_FOR_STRING("N",SDLK_n);
		KEYCODE_FOR_STRING("O",SDLK_o);
		KEYCODE_FOR_STRING("P",SDLK_p);
		KEYCODE_FOR_STRING("Q",SDLK_q);
		KEYCODE_FOR_STRING("R",SDLK_r);
		KEYCODE_FOR_STRING("S",SDLK_s);
		KEYCODE_FOR_STRING("T",SDLK_t);
		KEYCODE_FOR_STRING("U",SDLK_u);
		KEYCODE_FOR_STRING("V",SDLK_v);
		KEYCODE_FOR_STRING("W",SDLK_w);
		KEYCODE_FOR_STRING("X",SDLK_x);
		KEYCODE_FOR_STRING("Y",SDLK_y);
		KEYCODE_FOR_STRING("Z",SDLK_z);
		
		// Note: Just 0-9 will be cloned to KEYBOARD and NUMPAD variants
		KEYCODE_FOR_STRING("KEYBOARD0",SDLK_0);
		KEYCODE_FOR_STRING("KEYBOARD1",SDLK_1);
		KEYCODE_FOR_STRING("KEYBOARD2",SDLK_2);
		KEYCODE_FOR_STRING("KEYBOARD3",SDLK_3);
		KEYCODE_FOR_STRING("KEYBOARD4",SDLK_4);
		KEYCODE_FOR_STRING("KEYBOARD5",SDLK_5);
		KEYCODE_FOR_STRING("KEYBOARD6",SDLK_6);
		KEYCODE_FOR_STRING("KEYBOARD7",SDLK_7);
		KEYCODE_FOR_STRING("KEYBOARD8",SDLK_8);
		KEYCODE_FOR_STRING("KEYBOARD9",SDLK_9);
		
		KEYCODE_FOR_STRING("NUMPAD0",SDLK_KP0); // KP_
		KEYCODE_FOR_STRING("NUMPAD1",SDLK_KP1);
		KEYCODE_FOR_STRING("NUMPAD2",SDLK_KP2);
		KEYCODE_FOR_STRING("NUMPAD3",SDLK_KP3);
		KEYCODE_FOR_STRING("NUMPAD4",SDLK_KP4);
		KEYCODE_FOR_STRING("NUMPAD5",SDLK_KP5);
		KEYCODE_FOR_STRING("NUMPAD6",SDLK_KP6);
		KEYCODE_FOR_STRING("NUMPAD7",SDLK_KP7);
		KEYCODE_FOR_STRING("NUMPAD8",SDLK_KP8);
		KEYCODE_FOR_STRING("NUMPAD9",SDLK_KP9);
		
		// The following numpad keys are not expanded by cloning
//		KEYCODE_FOR_STRING("NUMPAD00",SDLK_KP00);
//		KEYCODE_FOR_STRING("NUMPAD000",SDLK_KP000);
		
		KEYCODE_FOR_STRING("NUMPAD/",SDLK_KP_DIVIDE);
		KEYCODE_FOR_STRING("NUMPADSLASH",SDLK_KP_DIVIDE);
		KEYCODE_FOR_STRING("NUMPADDIVIDE",SDLK_KP_DIVIDE);
		
		KEYCODE_FOR_STRING("NUMPAD+",SDLK_KP_PLUS);
		KEYCODE_FOR_STRING("NUMPADPLUS",SDLK_KP_PLUS);
		
		KEYCODE_FOR_STRING("NUMPAD*",SDLK_KP_MULTIPLY);
		KEYCODE_FOR_STRING("NUMPADMULTIPLY",SDLK_KP_MULTIPLY);
		KEYCODE_FOR_STRING("NUMPADSTAR",SDLK_KP_MULTIPLY);
		
		KEYCODE_FOR_STRING("NUMPAD-",SDLK_KP_MINUS);
		KEYCODE_FOR_STRING("NUMPADMINUS",SDLK_KP_MINUS);
		
		KEYCODE_FOR_STRING("NUMPAD.",SDLK_KP_PERIOD);
		KEYCODE_FOR_STRING("NUMPADPERIOD",SDLK_KP_PERIOD);
		
		KEYCODE_FOR_STRING("NUMPADENTER",SDLK_KP_ENTER);
		KEYCODE_FOR_STRING("NUMPADRETURN",SDLK_KP_ENTER);
		
		
		KEYCODE_FOR_STRING("TAB",SDLK_TAB);
		KEYCODE_FOR_STRING("SPACE",SDLK_SPACE);
		
		KEYCODE_FOR_STRING("UP",SDLK_UP); // arrow keys
		KEYCODE_FOR_STRING("DOWN",SDLK_DOWN);
		KEYCODE_FOR_STRING("LEFT",SDLK_LEFT);
		KEYCODE_FOR_STRING("RIGHT",SDLK_RIGHT);
		
		KEYCODE_FOR_STRING("`",SDLK_BACKQUOTE); // SDLK_GRAVE
		KEYCODE_FOR_STRING("BACKTICK",SDLK_BACKQUOTE);
		KEYCODE_FOR_STRING("GRAVE",SDLK_BACKQUOTE);
		
		KEYCODE_FOR_STRING("-",SDLK_MINUS);
		KEYCODE_FOR_STRING("MINUS",SDLK_MINUS);
		
		KEYCODE_FOR_STRING("=",SDLK_EQUALS);
		KEYCODE_FOR_STRING("EQUALS",SDLK_EQUALS);
		
		KEYCODE_FOR_STRING("[",SDLK_LEFTBRACKET);
		KEYCODE_FOR_STRING("LEFTBRACKET",SDLK_LEFTBRACKET);
		
		KEYCODE_FOR_STRING("]",SDLK_RIGHTBRACKET);
		KEYCODE_FOR_STRING("RIGHTBRACKET",SDLK_RIGHTBRACKET);
		
		KEYCODE_FOR_STRING("\\",SDLK_BACKSLASH);
		KEYCODE_FOR_STRING("BACKSLASH",SDLK_BACKSLASH);
		
		KEYCODE_FOR_STRING(";",SDLK_SEMICOLON);
		KEYCODE_FOR_STRING("SEMICOLON",SDLK_SEMICOLON);
		
		KEYCODE_FOR_STRING("'",SDLK_QUOTE); // SDLK_APOSTROPHE
		KEYCODE_FOR_STRING("APOSTROPHE",SDLK_QUOTE);
		KEYCODE_FOR_STRING("QUOTE",SDLK_QUOTE);
		
		KEYCODE_FOR_STRING(",",SDLK_COMMA);
		KEYCODE_FOR_STRING("COMMA",SDLK_COMMA);
		
		KEYCODE_FOR_STRING(".",SDLK_PERIOD);
		KEYCODE_FOR_STRING("PERIOD",SDLK_PERIOD);
		
		KEYCODE_FOR_STRING("/",SDLK_SLASH);
		KEYCODE_FOR_STRING("SLASH",SDLK_SLASH);
		
		KEYCODE_FOR_STRING("ESCAPE",SDLK_ESCAPE);
		KEYCODE_FOR_STRING("ESC",SDLK_ESCAPE);
		
		KEYCODE_FOR_STRING("F1",SDLK_F1);
		KEYCODE_FOR_STRING("F2",SDLK_F2);
		KEYCODE_FOR_STRING("F3",SDLK_F3);
		KEYCODE_FOR_STRING("F4",SDLK_F4);
		KEYCODE_FOR_STRING("F5",SDLK_F5);
		KEYCODE_FOR_STRING("F6",SDLK_F6);
		KEYCODE_FOR_STRING("F7",SDLK_F7);
		KEYCODE_FOR_STRING("F8",SDLK_F8);
		KEYCODE_FOR_STRING("F9",SDLK_F9);
		KEYCODE_FOR_STRING("F10",SDLK_F10);
		KEYCODE_FOR_STRING("F11",SDLK_F11);
		KEYCODE_FOR_STRING("F12",SDLK_F12);
		KEYCODE_FOR_STRING("F13",SDLK_F13);
		KEYCODE_FOR_STRING("F14",SDLK_F14);
		KEYCODE_FOR_STRING("F15",SDLK_F15);
/*		KEYCODE_FOR_STRING("F16",SDLK_F16);
		KEYCODE_FOR_STRING("F17",SDLK_F17);
		KEYCODE_FOR_STRING("F18",SDLK_F18);
		KEYCODE_FOR_STRING("F19",SDLK_F19);
		KEYCODE_FOR_STRING("F20",SDLK_F20);
		KEYCODE_FOR_STRING("F21",SDLK_F21);
		KEYCODE_FOR_STRING("F22",SDLK_F22);
		KEYCODE_FOR_STRING("F23",SDLK_F23);
		KEYCODE_FOR_STRING("F24",SDLK_F24);
*/
		
		// Mac's "backspace" key is labled Delete. And there was much -rejoicing- confusion.
		// Note that elsewhere, ANYDELETE will have been cloned to both BACKSPACE and DELETE.
		KEYCODE_FOR_STRING("BACKSPACE",SDLK_BACKSPACE);
		KEYCODE_FOR_STRING("MACDELETE",SDLK_BACKSPACE);
		
		KEYCODE_FOR_STRING("DELETE",SDLK_DELETE);
		KEYCODE_FOR_STRING("FORWARDDELETE",SDLK_DELETE);
		
		// Mac's return key is where everyone else puts enter... Luckily the other one is keypad :) 
		KEYCODE_FOR_STRING("ENTER",SDLK_RETURN);
		KEYCODE_FOR_STRING("RETURN",SDLK_RETURN);
		
		// I have no idea what SDLK_RETURN2 is :( 
		
		std::cerr << "OH SNAP! |" << key << "|" << std::endl;
		return 0;
	}
	Uint16 InputMethodParser::GetKeycodeForStringModifier(const std::string key) // needs to be upper cased before coming here
	{
		if(!key.size())
			return 0;
		// Modifiers
		// NOTE: A previous pass will have cloned all these names, SANS direction
		// So, if you see "RIGHTFOO" below, "FOO" is also valid, and means either Right OR Left foo.
		KEYCODE_FOR_STRING("RIGHTALT",SDLK_RALT);
		KEYCODE_FOR_STRING("RIGHTOPT",SDLK_RALT);
		KEYCODE_FOR_STRING("LEFTALT",SDLK_LALT);
		KEYCODE_FOR_STRING("LEFTOPT",SDLK_LALT);
		
		KEYCODE_FOR_STRING("RIGHTCTRL",SDLK_RCTRL);
		KEYCODE_FOR_STRING("RIGHTCONTROL",SDLK_RCTRL);
		KEYCODE_FOR_STRING("LEFTCTRL",SDLK_LCTRL);
		KEYCODE_FOR_STRING("LEFTCONTROL",SDLK_LCTRL);
		
		KEYCODE_FOR_STRING("RIGHTGUI",SDLK_RMETA); // SDLK_RGUI, SDLK_LGUI
		KEYCODE_FOR_STRING("RIGHTWINDOWS",SDLK_RMETA);
		KEYCODE_FOR_STRING("RIGHTMETA",SDLK_RMETA);
		KEYCODE_FOR_STRING("RIGHTAPPLE",SDLK_RMETA);
		KEYCODE_FOR_STRING("RIGHTCOMMAND",SDLK_RMETA);
		KEYCODE_FOR_STRING("RIGHTCMD",SDLK_RMETA);
		KEYCODE_FOR_STRING("LEFTGUI",SDLK_LMETA);
		KEYCODE_FOR_STRING("LEFTWINDOWS",SDLK_LMETA);
		KEYCODE_FOR_STRING("LEFTMETA",SDLK_LMETA);
		KEYCODE_FOR_STRING("LEFTAPPLE",SDLK_LMETA);
		KEYCODE_FOR_STRING("LEFTCOMMAND",SDLK_LMETA);
		KEYCODE_FOR_STRING("LEFTCMD",SDLK_LMETA);
		
		KEYCODE_FOR_STRING("RIGHTSHIFT",SDLK_RSHIFT);
		KEYCODE_FOR_STRING("RIGHTSHIFT",SDLK_RSHIFT);
		KEYCODE_FOR_STRING("LEFTSHIFT",SDLK_LSHIFT);
		KEYCODE_FOR_STRING("LEFTSHIFT",SDLK_LSHIFT);

		std::cerr << "OH SNAP! |" << key << "|" << std::endl;
		return 0;
	}

	
	std::string* InputMethodParser::NormalizedCopy(const std::string in){
		int max=in.length();
		char* ret=new char[max+1];
		ret[max]='\0';
		const char* s=in.c_str();
		int j=0;
		for(int i=0;i<max;++i){
			if(s[i]==' ' || s[i]=='_' || s[i]=='\t')continue;
			if(s[i]>='a' && s[i]<='z')
				ret[j++]=s[i]&0xDF; // upper case;
			else
				ret[j++]=s[i];
		}
		ret[j]='\0';
		std::string* ret_s=new std::string(ret);
		delete[](ret);
		return ret_s;
	}
	

	
	// Lines are of the form action : expression && expression || expression ...
	InteractionController* InputMethodParser::ParseLine(std::string line,InteractionBridgeDictionary* dict)
	{
		std::string* norm=NormalizedCopy(line);
		
		std::vector<std::string> tokens;
		
		int last=norm->find(":");
		if(last==-1)
			return NULL;
		
		// Tokenize
		std::string name=norm->substr(0,last);
		last++;
		while(true)
		{
			int next1=norm->find(AND_TOKEN,last);
			int next2=norm->find(OR_TOKEN,last);
			if(next1==-1)next1=next2;
			if(next1>next2 && next2!=-1)next1=next2;
			if(next1==-1)break;
			tokens.push_back(norm->substr(last,(next1-last)));
			tokens.push_back(norm->substr(next1,2));
			last=next1+2;
		}
		tokens.push_back(norm->substr(last,norm->size()-last));
		delete(norm);
		// end tokenize
		
		// infixize
		std::vector<std::string> ops;
		std::vector<std::string> main;
		int max=tokens.size();
		for(int i=0;i<max;++i)
		{
			if(tokens[i]==OR_TOKEN){
				while(ops.size()&&ops.back()==AND_TOKEN){
					main.push_back(AND_TOKEN);
					ops.pop_back();
				}
				ops.push_back(OR_TOKEN);
			}
			else if(tokens[i]==AND_TOKEN){
				ops.push_back(AND_TOKEN);
			}
			else main.push_back(tokens[i]);
		}
		while(ops.size())
		{
			main.push_back(ops.back());
			ops.pop_back();
		}
		// end infixize;
		
		// perform any cloning that is required
		// The following things are cloned:
		//	KEY(0-9) -> KEY(KEYBOARD0-9), KEY(NUMPAD0-9)
		//  KEY(ANYDELETE) -> KEY(BACKSPACE), KEY(DELETE)
		//  MODIFIERKEY(ALT|OPT|CTRL|CONTROL|GUI|WINDOWS|META|APPLE|COMMAND|CMD|SHIFT) -> MODIFIERKEY(RIGHTfoo),MODIFIERKEY(LEFTfoo)
		for(unsigned int i=0;i<main.size();++i){
			if(main[i]==AND_TOKEN || main[i]==OR_TOKEN)continue;
			CLONE_IF_EQUAL("KEY(0)","KEY(KEYBOARD0)","KEY(NUMPAD0)");
			CLONE_IF_EQUAL("KEY(1)","KEY(KEYBOARD1)","KEY(NUMPAD1)");
			CLONE_IF_EQUAL("KEY(2)","KEY(KEYBOARD2)","KEY(NUMPAD2)");
			CLONE_IF_EQUAL("KEY(3)","KEY(KEYBOARD3)","KEY(NUMPAD3)");
			CLONE_IF_EQUAL("KEY(4)","KEY(KEYBOARD4)","KEY(NUMPAD4)");
			CLONE_IF_EQUAL("KEY(5)","KEY(KEYBOARD5)","KEY(NUMPAD5)");
			CLONE_IF_EQUAL("KEY(6)","KEY(KEYBOARD6)","KEY(NUMPAD6)");
			CLONE_IF_EQUAL("KEY(7)","KEY(KEYBOARD7)","KEY(NUMPAD7)");
			CLONE_IF_EQUAL("KEY(8)","KEY(KEYBOARD8)","KEY(NUMPAD8)");
			CLONE_IF_EQUAL("KEY(9)","KEY(KEYBOARD9)","KEY(NUMPAD9)");
			CLONE_IF_EQUAL("KEY(ANYDELETE)","KEY(BACKSPACE)","KEY(DELETE)");
			
			CLONE_IF_EQUAL("MODIFIERKEY(ALT)","MODIFIERKEY(LEFTALT)","MODIFIERKEY(RIGHTALT)");
			CLONE_IF_EQUAL("MODIFIERKEY(OPT)","MODIFIERKEY(LEFTOPT)","MODIFIERKEY(RIGHTOPT)");
			CLONE_IF_EQUAL("MODIFIERKEY(CTRL)","MODIFIERKEY(LEFTCTRL)","MODIFIERKEY(RIGHTCTRL)");
			CLONE_IF_EQUAL("MODIFIERKEY(CONTROL)","MODIFIERKEY(LEFTCONTROL)","MODIFIERKEY(RIGHTCONTROL)");
			CLONE_IF_EQUAL("MODIFIERKEY(GUI)","MODIFIERKEY(LEFTGUI)","MODIFIERKEY(RIGHTGUI)");
			CLONE_IF_EQUAL("MODIFIERKEY(WINDOWS)","MODIFIERKEY(LEFTWINDOWS)","MODIFIERKEY(RIGHTWINDOWS)");
			CLONE_IF_EQUAL("MODIFIERKEY(META)","MODIFIERKEY(LEFTMETA)","MODIFIERKEY(RIGHTMETA)");
			CLONE_IF_EQUAL("MODIFIERKEY(APPLE)","MODIFIERKEY(LEFTAPPLE)","MODIFIERKEY(RIGHTAPPLE)");
			CLONE_IF_EQUAL("MODIFIERKEY(COMMAND)","MODIFIERKEY(LEFTCOMMAND)","MODIFIERKEY(RIGHTCOMMAND)");
			CLONE_IF_EQUAL("MODIFIERKEY(CMD)","MODIFIERKEY(LEFTCMD)","MODIFIERKEY(RIGHTCMD)");
			CLONE_IF_EQUAL("MODIFIERKEY(SHIFT)","MODIFIERKEY(LEFTSHIFT)","MODIFIERKEY(RIGHTSHIFT)");
		}
//		for(unsigned int i=0;i<main.size();++i)
//			std::cerr << main[i] << " ";
//		std::cerr << std::endl;
		// end cloning
		return new InteractionController(name,new InteractionBooleanExpression(&main),dict);
	}
	
	void InputMethodParser::CloneInto(std::vector<std::string>* vec,unsigned int index,const char* first,const char* second){
		unsigned int max=vec->size();
		vec->at(index).assign(first);
		for(unsigned int i=0;i<index;++i)
			vec->push_back(vec->at(i));
		vec->push_back(second);
		for(unsigned int i=index+1;i<max;++i)
			vec->push_back(vec->at(i));
		vec->push_back(OR_TOKEN);
	}
	
	InputMethodParser::InputMethodParser(std::string file)
	{
		ConfigFile.open(file.c_str());
	}
	
	MasterInteractionController* InputMethodParser::ParseFile(InteractionBridgeDictionary* dict)
	{
		std::vector<InteractionController*> vec;
		while(ConfigFile.good()){
			std::string line;
			getline(ConfigFile,line);
			InteractionController* ibe=ParseLine(line,dict);// returns null if the line isn't valid
			if(ibe)
				vec.push_back(ibe);
		}
		
		InteractionController** ret=new InteractionController*[vec.size()];
		for(unsigned int i=0;i<vec.size();++i){
			ret[i]=vec[i];
			if(!ret[i]->IsValid()){
				for(unsigned int j=0;j<vec.size();++j)delete(vec[j]);
				delete[] ret;
				return NULL;
			}
		}
		return new MasterInteractionController(vec.size(),ret);
	}
} // namespace __RocEye__
