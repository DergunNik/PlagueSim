#include "who.h"

WHO::WHO(QObject *parent)
    : QObject{parent}
{}


WHO::WHO(Statistics *stat, CityManager* cityManager, QObject *parent) :
    QObject{parent},
    _stat(stat),
    _cityManager(cityManager)
{}


void WHO::checkState()
{
    auto state = _stat->history().back();
    float percent = static_cast<float>(state.haveSymptoms) / state.alive;
    if (!_firstCase && state.haveSymptoms) {
        _firstCase = true;
        emit news(QString("В городе обнаружен нулевой пациент неизвестного заболевания. "
                          "Врачи просят не поддаваться панике."));
    }
    if (!_hands && percent > REC_LEVEL) {
        _hands = true;
        emit news(QString("В связи с распространением нового заболевания врачи просят граждан "
                          "тщательно мыть руки и избегать людей, проявляющих признаки простуты."));
    }
    if (!_masks && percent > MASKS_LEVEL) {
        provideMasks();
    }
    if (!_firstDeath && state.dead) {
        _firstDeath = true;
        emit news(QString("Сообщается о первой смерти от новой болезни. Врачи выражают обеспокенность."));
    }
    if (!_minimalContacts && percent > MIN_CONT_LEVEL) {
        provideMinimalContacts();
    }
    if (!_vaccination && percent > VACCINE_LEVEL) {
        provideVaccination();
    }
    if (!_selfIsolation && percent > ISOLATION_LEVEL) {
        provideSelfIsolation();
    }
    if (!_hospitalIsFull && !_cityManager->placesLeft()) {
        _hospitalIsFull = true;
        emit news(QString("Администрация городской больницы заявляет о её переполнении - свободных мест не осталось."));
    }
    if (!_halfIsInf && percent > HALF_LEVEL) {
        _halfIsInf = true;
        emit news(QString("Каждый второй в городе болен! \"Я здоров - а Вы?\" - спрашивает главврач больницы."));
    }
    if (!_halfIsDead && state.dead > state.alive) {
        _halfIsDead = true;
        emit news(QString("Каждый второй в городе скончался из-за новой болезни. "
                          "Да когда же это кончится?"));
    }
    if (qAbs(1 - percent) <= PRECISION && !_everyIsInf) {
        _everyIsInf = true;
        emit news(QString("\"Да не может каждый, вот прямо кажк-кх-кхех... "
                          "Извините, вот прямо каждый болеть. Не верю,\" - заявляет Мэр города."));
    }
    if (_firstCase && !_end && percent <= PRECISION && state.alive) {
        _end = true;
        emit news(QString("\"Ну вот и всё,\" - цитата Мэра. "
                          "Город пережил очередную эпидемию."));
    }
    if (!_allDead && !state.alive) {
        _allDead = true;
        emit news(QString("С огорчением вынуждены сообщить, что последний житель Города только что умер."
                          "На этом всё."));
    }
}


void WHO::provideMasks()
{
    _masks = true;
    QString text = "Врачи указывают на растущие цифры заражённых новой болезнью,\n"
                   "они рекомендуют носить медицинские маски, независимо от вашего самочуствия!";

    News *dialog = new News(QPixmap(":/masks"), text);
    dialog->show();

    for (auto& now : _cityManager->citizens()) {
        if (now.responsibility() == RESPONSIBLE) {
            now.setIsWearingMask(true);
        }
    }

    emit news(text);
}


void WHO::provideMinimalContacts()
{
    _minimalContacts = true;
    QString text = "Врачи заявляют, что новой болезнью заражён каждый десятый житель города.\n"
                   "Они настоятельно рекомендуют воздержаться от любых личных контактов или свести их к минимуму!";

    News *dialog = new News(QPixmap(":/distance"), text);
    dialog->show();

    for (auto& now : _cityManager->citizens()) {
        if (now.responsibility() == RESPONSIBLE) {
            now.setSociability(now.sociability() / 2);
        }
    }

    emit news(text);
}


void WHO::provideVaccination()
{
    _vaccination = true;
    QString text = "\"20% города жалуется на симптомы новой болезни,\" - заявляют медики.\n"
                   "В связи с этим они призывают всех невакцинированных людей срочно это исправить,\n"
                   "чтобы обезопасить свою жизнь и жизни близких!";

    News *dialog = new News(QPixmap(":/vaccine"), text);
    dialog->show();

    for (auto& now : _cityManager->citizens()) {
        if (now.responsibility() == RESPONSIBLE && !now.isVaccinated()) {
            now.getVaccinated();
        }
    }

    emit news(text);
}


void WHO::provideSelfIsolation()
{
    _selfIsolation = true;
    QString text = "Как минимум каждый третий житель города заражён новой болезнью!\n"
                   "Врачи призывают население к немедленной самоизоляции!";

    News *dialog = new News(QPixmap(":/isolation"), text);
    dialog->show();

    for (auto& now : _cityManager->citizens()) {
        if (now.responsibility() == RESPONSIBLE) {
            now.setIsOnSelfIsolation(true);
        }
    }

    emit news(text);
}


void WHO::toHospital(Citizen& citizen, CityManager* cityManager)
{
    if (citizen.hasSyptoms() && citizen.responsibility() != IRRESPONSIBLE && !citizen.isInHospital() && cityManager->placesLeft()) {
        cityManager->takeHospitalPlace();
        citizen.setIsInHospital(true);
    } else if (!citizen.hasSyptoms() && citizen.isInHospital()) {
        cityManager->freeHospitalPlace();
        citizen.setIsInHospital(false);
    }
}
