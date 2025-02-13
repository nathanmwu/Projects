from pyswip import Prolog
from openai import OpenAI

client = OpenAI()
prolog = Prolog()

conversation_history = [
    {"role": "system", "content": "You are a Prolog expert who translates logical statements and queries into Prolog code."}
]

def chat_with_openai(user_input):
    # Append user input to the conversation history
    conversation_history.append({"role": "user", "content": user_input})
    response = client.chat.completions.create(
            model="gpt-4o-mini",
            messages=conversation_history,
            temperature=0
        )
    model_response = response.choices[0].message.content
    conversation_history.append({"role": "assistant", "content": model_response})
    
    return model_response

if __name__ == "__main__":

    # define query from user input
    question = input("Question: ")

    # define knowledge base
    with open("knowledge_base.pl", "r") as file:
        kb = file.read()    
    chat_with_openai("Here is a simple knowledge base about the Simpsons:\n{}".format(kb))

    # translate question into prolog query
    query = chat_with_openai("Translate the following question into a Prolog query based on the previous prolog knowledge base. Do not use any predicates or rules that are not specified in the knowledge base. Do not make any comments in prolog, and remove the leading '?-'. This query should be able to be directly fed into pyswip's 'query' function:\n{}".format(question))
    query = ("\n".join(query.split("\n")[1:-1]))

    print("\n--------Translated Query---------\n")
    print(query)
    
    # use symbolic solver
    prolog.consult('knowledge_base.pl')
    query_result = []
    for res in prolog.query(query):
        query_result.append(res)

    print("\n--------Query Result---------\n")
    print(query_result)

    # interpret result and translate back into natural language
    query_response = chat_with_openai("Given the following result of the previous query, answer the original question. Answer the question succinctly, and do not mention the original question or the prolog query.\nOriginal question: {}\nQuery result: {}".format(question, str(query_result)))
    
    print("\n--------Natural Language Response---------\n")
    print(query_response)
    
    

