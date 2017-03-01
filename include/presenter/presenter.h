#ifndef PRESENTER_H
#define PRESENTER_H

class Presenter
{
  public:
                                                Presenter();

    virtual void                                init();

    virtual void                                update();

    void                                        setModel(std::shared_ptr<Model> model);
    void                                        notifyChangeToModel();

  protected:
    std::function<void()>                       _notifyChangeToModelCallback;

    View                                        _view;

    std::shared_ptr<Model>                      _model;
};

#endif // PRESENTER_H
