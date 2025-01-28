from pyswip import Prolog
from openai import OpenAI

client = OpenAI()

def get_model_response(prompt, model="gpt-4o-mini"):
    # Gets a response from the OpenAI API for a given prompt.
    # Parameters:
    #    prompt (str): The input prompt for the OpenAI model.
    #    model (str): The model to use for the completion.
    response = client.chat.completions.create(
            model=model,
            messages=[
                {
                    "role": "user",
                    "content": prompt
                }
            ]
        )
    return response.choices[0].message.content

if __name__ == "__main__":
    prompt = "How are nature and individual identity connected?"
    print("Generating natural language response")
    response = get_model_response(prompt)
    prompt = "Translate the following text into Prolog but don't say anything else. Your reponse should be 100% Prolog, as if it were written in a Prolog file.:\n{}".format(response)
    print("Translating response into Prolog")
    prolog_translation = get_model_response(prompt)

    prolog_code = "\n".join(prolog_translation.split("\n")[1:-1])
    with open("knowledge_base.pl", "w") as file:
        file.write(prolog_code)

    prolog = Prolog()
    prolog.consult('knowledge_base.pl')
    print("Done")
    