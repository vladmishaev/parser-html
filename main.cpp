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
        
        string deleteSpaceByEqual(string strHtml)
        {
            string editedStrHtml = "";
            regex getEqualWSpace(R"((\s+=\s+)|(\s+=)|(=\s+))");

            return editedStrHtml;
        }

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
            
            regex reg(R"([a-z0-9-]+="[a-zA-Z0-9-_]+")");
            smatch match;

            while(regex_search(teg, match, reg))
            {
                string atrWValue = match[0].str();
                regex patDivide("=");

                vector<string> dividedString(
                        sregex_token_iterator(atrWValue.begin(), atrWValue.end(), patDivide,-1),
                        sregex_token_iterator()
                        );

                string attribute = dividedString[0];
                string value = dividedString[1];

                AtrList[attribute] = value;
                teg = match.suffix();

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
                    
                    teg.attributes = getAtributesList(*str);

                    nestingLevel.push(&teg);
                                    
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

    string HtmlCode = "<tag1 value=\"value\">"
                      "<tag2 name=\"vlad\">"
                      "<tag3 another=\"1\" final=\"56\">"
                      "</tag3>"
                      "</tag2>"
                      "</tag1>";

    HtmlDocument tes(HtmlCode);

    return 0;
}
