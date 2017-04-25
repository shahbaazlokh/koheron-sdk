/// {{ driver.class_name|lower }}.hpp
///
/// Autogenerated DO NOT EDIT
///
/// (c) Koheron

#ifndef __{{ driver.class_name|upper }}_HPP__
#define __{{ driver.class_name|upper }}_HPP__

#include <memory>
#include <mutex>

#include <driver.hpp>

{% for include in driver.includes -%}
#include "{{ include }}"
{% endfor -%}

namespace koheron {

template<>
class Driver<driver_id_of<{{ driver.objects[0]["type"] }}>> : public DriverAbstract
{
  public:
    int execute(Command& cmd);
    template<int op> int execute_operation(Command& cmd);

    Driver(Server *server_, {{ driver.objects[0]["type"] }}& {{ driver.objects[0]["name"] }}_)
    : DriverAbstract(driver_id_of<{{ driver.objects[0]["type"] }}>, server_)
    , {{ driver.objects[0]["name"] }}({{ driver.objects[0]["name"] }}_)
    {}

    enum Operation {
        {% for operation in driver.operations -%}
        {{ operation['tag'] }} = {{ operation['id'] }},
        {% endfor -%}
        {{ driver.tag|lower }}_op_num
    };

    std::mutex mutex;

    {{ driver.objects[0]["type"] }}& {{ driver.objects[0]["name"] }};

{% for operation in driver.operations -%}
struct Argument_{{ operation['name'] }} {
{%- macro print_param_line(arg) %}
        {{ arg["type"] }} {{ arg["name"]}};
{%- endmacro -%}
{% for arg in operation["arguments"] -%}
    {{ arg["type"] }} {{ arg["name"]}};
{% endfor -%}
} args_{{ operation['name'] }};

{% endfor -%}

}; // class Interface_{{ driver.tag|capitalize }}

} // namespace koheron

#endif //__{{ driver.class_name|upper }}_HPP__
