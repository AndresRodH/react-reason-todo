type todo = {
  text: string,
  completed: bool,
};

[@react.component]
let make = () => {
  let (todos, setTodos) = React.useState(() => []);
  let (newTodo, setNewTodo) = React.useState(() => "");
  let addTodo = _ =>
    if (String.trim(newTodo) != "") {
      setTodos(todos => [{text: newTodo, completed: false}, ...todos]);
      setNewTodo(_ => "");
    };

  <div
    style={ReactDOMRe.Style.make(
      ~display="flex",
      ~flex="1",
      ~justifyContent="center",
      ~alignItems="center",
      ~flexDirection="column",
      (),
    )}>
    <div>
      <input
        value=newTodo
        onChange={event => setNewTodo(event->ReactEvent.Form.target##value)}
        onKeyDown={evt =>
          if (ReactEvent.Keyboard.key(evt) == "Enter") {
            addTodo();
          }
        }
      />
      <button onClick=addTodo> {React.string("Submit")} </button>
    </div>
    <div>
      {List.mapi(
         (index, todo) =>
           <div
             style={ReactDOMRe.Style.make(
               ~display="grid",
               ~gridTemplateColumns="auto auto",
               ~width="300px",
               ~justifyItems="center",
               (),
             )}
             key={string_of_int(index)}>
             {React.string(todo.text)}
             <input type_="checkbox" checked={todo.completed} />
           </div>,
         todos,
       )
       |> Array.of_list
       |> React.array}
    </div>
  </div>;
};