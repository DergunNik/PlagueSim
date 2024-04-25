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
        emit news(QString("Сообщается о первой смерти от новой болезни. Врачи выражают обеспокоиность."));
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
        emit news(QString("Администрация городской больницы заявляет о переполнении больницы - свободных мест не осталось."));
    }
    if (!_halfIsInf && percent > HALF_LEVEL) {
        _halfIsInf = true;
        emit news(QString("Каждый второй в городе болен! \"Я здоров - а Вы?\" - спрашивают врачи."));
    }
    if (qAbs(1 - percent) <= ONE_PRECISION && !_everyIsInf) {
        _everyIsInf = true;
        emit news(QString("\"Да не может каждый, вот прямо кажк-кх-кхех... "
                          "Извините, вот прямо каждый болеть. Не верю,\" - заявляет Мэр города."));
    }
}


void WHO::provideMasks()
{
    _masks = true;

    for (auto& now : _cityManager->citizens()) {
        if (now.responsibility() == RESPONSIBLE) {
            now.setIsWearingMask(true);
        }
    }

    emit news(QString("Врачи указывают на растущие цифры заражённых новой болезнью,"
                      " они рекомендуют носить медицинские маски, независимо от вашего самочуствия."));
}


void WHO::provideMinimalContacts()
{
    _minimalContacts = true;

    for (auto& now : _cityManager->citizens()) {
        if (now.responsibility() == RESPONSIBLE) {
            now.setSociability(now.sociability() / 2);
        }
    }

    emit news(QString("Врачи заявляют, что новой болезнью заражён каждый десятый житель города."
                      "Они настоятельно рекомендуют воздержаться от любых личных контактов или свести их к минимуму."));
}


void WHO::provideVaccination()
{
    _vaccination = true;

    for (auto& now : _cityManager->citizens()) {
        if (now.responsibility() == RESPONSIBLE && !now.isVaccinated()) {
            now.getVaccinated();
        }
    }

    emit news(QString("\"20% города жалуется на симптомы новой болезни,\" - заявляют медики. "
                      "В связи с этим они призывают всех невакцинированных людей срочно это исправлять, "
                      "чтобы обезопасить свою жизнь и жизни близких."));
}


void WHO::provideSelfIsolation()
{
    _selfIsolation = true;

    for (auto& now : _cityManager->citizens()) {
        if (now.responsibility() == RESPONSIBLE) {
            now.setIsOnSelfIsolation(true);
        }
    }

    emit news(QString("Как минимум каждый третий житель города заражён новой болезнью! "
                      "Врачи призывают население к немедленной самоизоляции."));
}


void WHO::toHospital(Citizen& citizen, CityManager* cityManager)
{
    if (citizen.hasSyptoms() && !citizen.isInHospital() && cityManager->placesLeft()) {
        cityManager->takeHospitalPlace();
        citizen.setIsInHospital(true);
    } else if (!citizen.hasSyptoms() && citizen.isInHospital()) {
        cityManager->freeHospitalPlace();
        citizen.setIsInHospital(false);
    }
}
