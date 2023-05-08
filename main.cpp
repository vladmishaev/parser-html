#include <iterator>
#include <map>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <regex>
#include <vector>

using namespace std;

struct HtmlElement
{
    map<string, string> attributes;
    map<string, HtmlElement*> children;
};

class HtmlDocument
{
    public:

        HtmlDocument(string strHTML)
        {
            HTMLcode = strHTML;
            CreateHtmlDocument();
        }




    private:
        map<string, HtmlElement*> listHtmlElements;
        stack<HtmlElement*> nestingLevel;
        string HTMLcode;


        string getNameTeg(string teg)
        {
            regex reg("<[a-z0-9]+");
            smatch match;
            regex_search(teg, match, reg);

            string nameObj = match[0].str().erase(0,1);
            return nameObj;
        }

        map<string, string> getAtributesList(string teg)
        {
            map<string, string> AtrList;
            
            regex reg("[a-z-]+\\s*=\\s*\"[a-zA-Z0-9-_]+\"");
            smatch match;

            while(regex_search(teg, match, reg))
            {
                string attributeWValue = match[0].str();
                
                regex patternDivide("\\s*=\\s*");
                sregex_token_iterator begin(attributeWValue.begin(),attributeWValue.end(), 
                                            patternDivide,-1);
                sregex_token_iterator end;

                





            }
            
            
            









            return AtrList;

        }
 
        void fillLsHtmlElements(list<string> listHtmlT)
        {
        
            for(list<string>::iterator str = listHtmlT.begin(); str != listHtmlT.end(); str++)
            {
                if(str->find("</") != string::npos)
                {
                    nestingLevel.pop();
                }
                else 
                {

                    string name = getNameTeg(*str);             
                    HtmlElement teg;

    
                    if(nestingLevel.empty())
                    {
                        listHtmlElements[name] = &teg;

                    }
                    else
                    {
                        nestingLevel.top()->children[name] = &teg;
                    }


                                    
                }
            }

        }

        void CreateHtmlDocument()
        {
            list<string> AllTegsList = getAllTegs();
            fillLsHtmlElements(AllTegsList);

        }

        list<string> getAllTegs()
        {
            list<string> AllTegs;
            string HtmlTeg = "";

            for(int i = 0; i < HTMLcode.size(); i++)
            {
                if(HTMLcode[i] == '<')
                {
                    while(true)
                    {
                        HtmlTeg += HTMLcode[i];
                        if(HTMLcode[i] == '>') break;
                        i++;       
                    }

                    AllTegs.push_back(HtmlTeg);
                    HtmlTeg = "";
                }


            }

            return AllTegs;
        }

        
};




int main()
{

    string HtmlCode = "<tag1 value = \"value\">  fdfdfdsfsdfsd   dsfsdf"
                      " fsdfdsfdsfsdfsd   <tag2 name = \"name\">    fsdfsdfsdfsdsd  "
                      "<tag3 another=\"another\" final=\"final\">"
                      "</tag3>"
                      "</tag2>"
                      "</tag1>";

    

    return 0;
}
