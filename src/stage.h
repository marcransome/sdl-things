/* MIT License

  Copyright (c) 2021 Marc Ransome

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE. */

#ifndef STAGE_H
#define STAGE_H

/*!
 *  \file stage.h
 *
 *  \brief Header file providing a common interface for stage management.
 *
 *  The ::Stage type represents a generic game stage and is implemented
 *  as a polymorphic type using a virtual table of function pointers
 *  (i.e. the stage \e interface).
 *
 *  The process that follows describes the recommended way of
 *  implementing a new game stage:
 *
 *  - Define a new opaque type that represents the new game stage, such
 *    as `ExampleStage`, and implement a suitable constructor function
 *    (e.g. `ExampleStage * example_stage_new(void)`)
 *
 *  - Define the interface for the stage. This can be shared by all
 *    instances of the new stage type. For example, the following compound
 *    literal might be defined in `example.c`:
 *
 *        static StageInterface *example_interface = &(StageInterface) {
 *            .init = (void (*)(void *)) example_stage_init,
 *            .destroy = (void (*)(void *)) example_stage_destroy,
 *            .perform_logic = (void (*)(void *)) example_stage_perform_logic,
 *            .render_scene = (void (*)(void *)) example_stage_render_scene
 *        }
 *
 *  - Implement the functions named in the interface above in the same
 *    file (`example.c`). Prototypes for such functions would be written as:
 *
 *        static void example_stage_init(ExampleStage *example_stage);
 *        static void example_stage_destroy(ExampleStage *example_stage);
 *        static void example_stage_perform_logic(ExampleStage *example_stage);
 *        static void example_stage_render_scene(ExampleStage *example_stage);
 *
 * \note The function specified for the `destroy` field of the interface must
 *       free all resources that were allocated in the stage's constructor function,
 *       and will be called automatically when a ::Stage object is destroy
 *       via stage_destroy().
 *
 *  - Define a convenience function in the corresponding header file—`example.h`—
 *    this helps to encapsulate the interface:
 *
 *        StageInterface * example_stage_get_interface(void) {
 *            return example_interface;
 *        }
 *
 *  Having implemented all of the above, a new ::Stage object can be created in
 *  the following way:
 *
 *      Stage *stage = stage_new(example_stage_new(), example_stage_get_interface());
 */

/*! \brief A type representing the common polymorphic interface that all
 *         game stages should implement.
 */
typedef struct StageInterfaceData {
    /*! \brief A callback function that should be used to initialise a stage. */
    void (*init)(void *instance);

    /*! \brief A callback function that should be used to destroy a stage. */
    void (*destroy)(void *instance);

    /*! \brief A callback function that should be used to update a stage. */
    void (*perform_logic)(void *instance);

    /*! \brief A callback function that should be used to render a stage. */
    void (*render_scene)(void *instance);
} StageInterface;

/*! \typedef Stage
 *
 *  \brief A type representing a generic game stage.
 */
typedef struct StageData {
    void *instance;
    const StageInterface *interface;
} Stage;

/*! \brief Create a stage.
 *
 *  \param instance  A pointer to the concrete stage object.
 *  \param interface A pointer to the ::StageInterface for this stage type.
 *
 *  \return A pointer to a ::Stage object.
 */
Stage * stage_new(void *instance, StageInterface *interface);

/*! \brief Destroy a stage.
 *
 *  \param stage A pointer to the ::Stage object that should be destroyed.
 *
 *  \note Before the resources allocated for a ::Stage object are freed,
 *        the `destroy` function pointer of the interface that was
 *        provided at creation time (via stage_new()) will be called to
 *        destroy the underlying concrete type.
 *
 *  \return void
 */
void stage_destroy(Stage *stage);

/*! \brief Invoke the init function of a stage.
 *
 *  The `init` function of the interface that was provided at
 *  creation time (via stage_new()) will be called on the underlying
 *  concrete type. This function should implement any initialisation
 *  necessary to prepare the stage.
 *
 *  \param stage A pointer to the ::Stage object.
 *
 *  \return void
 */
void stage_init(Stage *stage);

/*! \brief Invoke the logic function of a stage.
 *
 *  The `perform_logic` function of the interface that was provided
 *  at creation time (via stage_new()) will be called on the underlying
 *  concrete type. This function should implement any logic routines
 *  necessary to update the stage and its entities.
 *
 *  \param stage A pointer to the ::Stage object.
 *
 *  \return void
 */
void stage_perform_logic(Stage *stage);

/*! \brief Invoke the rendering function of a stage.
 *
 *  The `render_scene` function of the interface that was provided
 *  at creation time (via stage_new()) will be called on the underlying
 *  concrete type. This function should implement any rendering
 *  routines necessary to draw the stage and its entities.
 *
 *  \param stage A pointer to the ::Stage object.
 *
 *  \return void
 */
void stage_render_scene(Stage *stage);

#endif /* !STAGE_H */
